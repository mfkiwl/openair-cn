/*
 * Licensed to the OpenAirInterface (OAI) Software Alliance under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The OpenAirInterface Software Alliance licenses this file to You under
 * the Apache License, Version 2.0  (the "License"); you may not use this file
 * except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *-------------------------------------------------------------------------------
 * For more information about the OpenAirInterface (OAI) Software Alliance:
 *      contact@openairinterface.org
 */

/*! \file 3gpp_24.008_gmm_ies.c
  \brief
  \author Lionel Gauthier
  \company Eurecom
  \email: lionel.gauthier@eurecom.fr
*/

#include <netinet/in.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>

#include "bstrlib.h"

#include "3gpp_23.003.h"
#include "3gpp_24.008.h"
#include "TLVDecoder.h"
#include "TLVEncoder.h"
#include "assertions.h"
#include "common_defs.h"
#include "log.h"

//******************************************************************************
// 10.5.5 GPRS mobility management information elements
//******************************************************************************

//------------------------------------------------------------------------------
// 10.5.5.4 TMSI status
//------------------------------------------------------------------------------
int decode_tmsi_status(tmsi_status_t *tmsistatus, const bool iei_present,
                       uint8_t *buffer, const uint32_t len) {
  int decoded = 0;

  CHECK_IEI_DECODER(GMM_TMSI_STATUS_IEI, (*buffer & 0xF0));
  *tmsistatus = *buffer & 0x1;
  decoded++;
  return decoded;
}

int encode_tmsi_status(tmsi_status_t *tmsistatus, const bool iei_present,
                       uint8_t *buffer, const uint32_t len) {
  uint8_t encoded = 0;

  /*
   * Checking length and pointer
   */
  CHECK_PDU_POINTER_AND_LENGTH_ENCODER(buffer, TMSI_STATUS_IE_MAX_LENGTH, len);
  *(buffer + encoded) =
      0x00 | (GMM_TMSI_STATUS_IEI & 0xf0) | (*tmsistatus & 0x1);
  encoded++;
  return encoded;
}

//------------------------------------------------------------------------------
// 10.5.5.6 DRX parameter
//------------------------------------------------------------------------------
int decode_drx_parameter_ie(drx_parameter_t *drxparameter,
                            const bool iei_present, uint8_t *buffer,
                            const uint32_t len) {
  int decoded = 0;

  if (iei_present) {
    CHECK_PDU_POINTER_AND_LENGTH_DECODER(buffer, DRX_PARAMETER_IE_MAX_LENGTH,
                                         len);
    CHECK_IEI_DECODER(GMM_DRX_PARAMETER_IEI, *buffer);
    decoded++;
  } else {
    CHECK_PDU_POINTER_AND_LENGTH_DECODER(
        buffer, (DRX_PARAMETER_IE_MAX_LENGTH - 1), len);
  }

  drxparameter->splitpgcyclecode = *(buffer + decoded);
  decoded++;
  drxparameter->cnspecificdrxcyclelengthcoefficientanddrxvaluefors1mode =
      (*(buffer + decoded) >> 4) & 0xf;
  drxparameter->splitonccch = (*(buffer + decoded) >> 3) & 0x1;
  drxparameter->nondrxtimer = *(buffer + decoded) & 0x7;
  decoded++;
  return decoded;
}

//------------------------------------------------------------------------------
int encode_drx_parameter_ie(drx_parameter_t *drxparameter,
                            const bool iei_present, uint8_t *buffer,
                            const uint32_t len) {
  uint32_t encoded = 0;

  if (iei_present) {
    CHECK_PDU_POINTER_AND_LENGTH_ENCODER(buffer, DRX_PARAMETER_IE_MAX_LENGTH,
                                         len);
    *buffer = GMM_DRX_PARAMETER_IEI;
    encoded++;
  } else {
    CHECK_PDU_POINTER_AND_LENGTH_ENCODER(
        buffer, (DRX_PARAMETER_IE_MAX_LENGTH - 1), len);
  }

  *(buffer + encoded) = drxparameter->splitpgcyclecode;
  encoded++;
  *(buffer + encoded) =
      0x00 |
      ((drxparameter->cnspecificdrxcyclelengthcoefficientanddrxvaluefors1mode &
        0xf)
       << 4) |
      ((drxparameter->splitonccch & 0x1) << 3) |
      (drxparameter->nondrxtimer & 0x7);
  encoded++;
  return encoded;
}

//------------------------------------------------------------------------------
// 10.5.5.8 P-TMSI signature
//------------------------------------------------------------------------------
int decode_p_tmsi_signature_ie(p_tmsi_signature_t *ptmsisignature,
                               const bool iei_present, uint8_t *buffer,
                               const uint32_t len) {
  int decoded = 0;

  if (iei_present) {
    CHECK_PDU_POINTER_AND_LENGTH_DECODER(buffer, P_TMSI_SIGNATURE_IE_MAX_LENGTH,
                                         len);
    CHECK_IEI_DECODER(GMM_PTMSI_SIGNATURE_IEI, *buffer);
    decoded++;
  } else {
    CHECK_PDU_POINTER_AND_LENGTH_DECODER(
        buffer, (P_TMSI_SIGNATURE_IE_MAX_LENGTH - 1), len);
  }

  IES_DECODE_U32(buffer, decoded, *ptmsisignature);
  return decoded;
}

//------------------------------------------------------------------------------
int encode_p_tmsi_signature_ie(p_tmsi_signature_t ptmsisignature,
                               const bool iei_present, uint8_t *buffer,
                               const uint32_t len) {
  uint32_t encoded = 0;

  if (iei_present) {
    CHECK_PDU_POINTER_AND_LENGTH_ENCODER(buffer, P_TMSI_SIGNATURE_IE_MAX_LENGTH,
                                         len);
    *buffer = GMM_PTMSI_SIGNATURE_IEI;
    encoded++;
  } else {
    CHECK_PDU_POINTER_AND_LENGTH_ENCODER(
        buffer, (P_TMSI_SIGNATURE_IE_MAX_LENGTH - 1), len);
  }

  IES_ENCODE_U32(buffer, encoded, ptmsisignature);
  return encoded;
}

//------------------------------------------------------------------------------
// 10.5.5.9 Identity type 2
//------------------------------------------------------------------------------
int decode_identity_type_2_ie(identity_type2_t *identitytype2,
                              bool is_ie_present, uint8_t *buffer,
                              const uint32_t len) {
  int decoded = 0;

  CHECK_PDU_POINTER_AND_LENGTH_DECODER(buffer, IDENTITY_TYPE_2_IE_MAX_LENGTH,
                                       len);

  if (is_ie_present) {
    AssertFatal(0, "No IEI for Identity type 2");
    CHECK_IEI_DECODER((*buffer & 0xf0), 0);
  }

  *identitytype2 = *buffer & 0x7;
  decoded++;
  return decoded;
}

//------------------------------------------------------------------------------
int encode_identity_type_2_ie(identity_type2_t *identitytype2,
                              bool is_ie_present, uint8_t *buffer,
                              const uint32_t len) {
  uint8_t encoded = 0;

  /*
   * Checking length and pointer
   */
  CHECK_PDU_POINTER_AND_LENGTH_ENCODER(buffer, IDENTITY_TYPE_2_IE_MAX_LENGTH,
                                       len);
  *(buffer + encoded) = 0x00;
  if (is_ie_present) {
    AssertFatal(0, "No IEI for Identity type 2");
    *(buffer + encoded) |= (0 & 0xf0);
  }
  *(buffer + encoded) |= (*identitytype2 & 0x7);
  encoded++;
  return encoded;
}

//------------------------------------------------------------------------------
// 10.5.5.10 IMEISV request
//------------------------------------------------------------------------------

int decode_imeisv_request_ie(imeisv_request_t *imeisvrequest,
                             bool is_ie_present, uint8_t *buffer,
                             const uint32_t len) {
  int decoded = 0;

  CHECK_PDU_POINTER_AND_LENGTH_DECODER(buffer, IMEISV_REQUEST_IE_MAX_LENGTH,
                                       len);

  if (is_ie_present) {
    CHECK_IEI_DECODER((*buffer & 0xf0), GMM_IMEISV_REQUEST_IEI);
  }

  *imeisvrequest = *buffer & 0x7;
  decoded++;
  return decoded;
}

//------------------------------------------------------------------------------
int encode_imeisv_request_ie(imeisv_request_t *imeisvrequest,
                             bool is_ie_present, uint8_t *buffer,
                             const uint32_t len) {
  uint8_t encoded = 0;

  /*
   * Checking length and pointer
   */
  CHECK_PDU_POINTER_AND_LENGTH_ENCODER(buffer, IMEISV_REQUEST_IE_MAX_LENGTH,
                                       len);
  *(buffer + encoded) = 0x00;
  if (is_ie_present) {
    *(buffer + encoded) = GMM_IMEISV_REQUEST_IEI & 0xf0;
  }
  *(buffer + encoded) |= (*imeisvrequest & 0x7);
  encoded++;
  return encoded;
}

//------------------------------------------------------------------------------
// 10.5.5.12 MS network capability
//------------------------------------------------------------------------------
int decode_ms_network_capability_ie(
    ms_network_capability_t *msnetworkcapability, const bool iei_present,
    uint8_t *buffer, const uint32_t len) {
  int decoded = 0;
  uint8_t ielen = 0;
  uint8_t b = 0;

  if (iei_present) {
    CHECK_PDU_POINTER_AND_LENGTH_DECODER(
        buffer, MS_NETWORK_CAPABILITY_IE_MIN_LENGTH, len);
    CHECK_IEI_DECODER(GMM_MS_NETWORK_CAPABILITY_IEI, *buffer);
    decoded++;
  } else {
    CHECK_PDU_POINTER_AND_LENGTH_DECODER(
        buffer, (MS_NETWORK_CAPABILITY_IE_MIN_LENGTH - 1), len);
  }

  DECODE_U8(buffer + decoded, ielen, decoded);
  CHECK_PDU_POINTER_AND_LENGTH_DECODER(buffer, ielen, len - decoded);
  memset(msnetworkcapability, 0, sizeof(ms_network_capability_t));
  OAILOG_TRACE(LOG_NAS_EMM, "decode_ms_network_capability_ie len = %d\n",
               ielen);
  CHECK_LENGTH_DECODER(len - decoded, ielen);

  b = *(buffer + decoded);
  msnetworkcapability->gea1 = (b & MS_NETWORK_CAPABILITY_GEA1) >> 7;
  msnetworkcapability->smdc =
      (b & MS_NETWORK_CAPABILITY_SM_CAP_VIA_DEDICATED_CHANNELS) >> 6;
  msnetworkcapability->smgc =
      (b & MS_NETWORK_CAPABILITY_SM_CAP_VIA_GPRS_CHANNELS) >> 5;
  msnetworkcapability->ucs2 = (b & MS_NETWORK_CAPABILITY_UCS2_SUPPORT) >> 4;
  msnetworkcapability->sssi =
      (b & MS_NETWORK_CAPABILITY_SS_SCREENING_INDICATOR) >> 2;
  msnetworkcapability->solsa = (b & MS_NETWORK_CAPABILITY_SOLSA) >> 1;
  msnetworkcapability->revli =
      (b & MS_NETWORK_CAPABILITY_REVISION_LEVEL_INDICATOR);
  decoded++;

  if (ielen > 1) {
    b = *(buffer + decoded);
    msnetworkcapability->pfc =
        (b & MS_NETWORK_CAPABILITY_PFC_FEATURE_MODE) >> 7;
    msnetworkcapability->egea =
        (b & (MS_NETWORK_CAPABILITY_GEA2 | MS_NETWORK_CAPABILITY_GEA3 |
              MS_NETWORK_CAPABILITY_GEA4 | MS_NETWORK_CAPABILITY_GEA5 |
              MS_NETWORK_CAPABILITY_GEA6 | MS_NETWORK_CAPABILITY_GEA7)) >>
        1;
    msnetworkcapability->lcs = (b & MS_NETWORK_CAPABILITY_LCS_VA);
    decoded++;

    if (ielen > 2) {
      b = *(buffer + decoded);
      msnetworkcapability->ps_ho_utran =
          (b & MS_NETWORK_CAPABILITY_PS_INTER_RAT_HO_GERAN_TO_UTRAN_IU) >> 7;
      msnetworkcapability->ps_ho_eutran =
          (b & MS_NETWORK_CAPABILITY_PS_INTER_RAT_HO_GERAN_TO_EUTRAN_S1) >> 6;
      msnetworkcapability->emm_cpc =
          (b & MS_NETWORK_CAPABILITY_EMM_COMBINED_PROCEDURE) >> 5;
      msnetworkcapability->isr = (b & MS_NETWORK_CAPABILITY_ISR) >> 4;
      msnetworkcapability->srvcc = (b & MS_NETWORK_CAPABILITY_SRVCC) >> 3;
      msnetworkcapability->epc_cap = (b & MS_NETWORK_CAPABILITY_EPC) >> 2;
      msnetworkcapability->nf_cap =
          (b & MS_NETWORK_CAPABILITY_NOTIFICATION) >> 1;
      msnetworkcapability->geran_ns =
          (b & MS_NETWORK_CAPABILITY_GERAN_NETWORK_SHARING);
      decoded++;
    }
  }
  return decoded;
}

//------------------------------------------------------------------------------
int encode_ms_network_capability_ie(
    ms_network_capability_t *msnetworkcapability, const bool iei_present,
    uint8_t *buffer, const uint32_t len) {
  uint8_t *lenPtr;
  uint32_t encoded = 0;

  /*
   * Checking IEI and pointer
   */
  CHECK_PDU_POINTER_AND_LENGTH_ENCODER(
      buffer, MS_NETWORK_CAPABILITY_IE_MIN_LENGTH, len);

  if (iei_present) {
    *buffer = GMM_MS_NETWORK_CAPABILITY_IEI;
    encoded++;
  }

  lenPtr = (buffer + encoded);
  encoded++;

  *(buffer + encoded) =
      ((msnetworkcapability->gea1 & 0x1) << 7) |  // spare coded as zero
      ((msnetworkcapability->smdc & 0x1) << 6) |
      ((msnetworkcapability->smgc & 0x1) << 5) |
      ((msnetworkcapability->ucs2 & 0x1) << 4) |
      ((msnetworkcapability->sssi & 0x3) << 2) |
      ((msnetworkcapability->solsa & 0x1) << 1) |
      (msnetworkcapability->revli & 0x1);
  encoded++;

  *(buffer + encoded) =
      ((msnetworkcapability->pfc & 0x1) << 7) |  // spare coded as zero
      ((msnetworkcapability->egea & 0x3F) << 1) |
      (msnetworkcapability->lcs & 0x1);
  encoded++;

  *(buffer + encoded) =
      ((msnetworkcapability->ps_ho_utran & 0x1) << 7) |  // spare coded as zero
      ((msnetworkcapability->ps_ho_eutran & 0x1) << 6) |
      ((msnetworkcapability->emm_cpc & 0x1) << 5) |
      ((msnetworkcapability->isr & 0x1) << 4) |
      ((msnetworkcapability->srvcc & 0x1) << 3) |
      ((msnetworkcapability->epc_cap & 0x1) << 2) |
      ((msnetworkcapability->nf_cap & 0x1) << 1) |
      (msnetworkcapability->geran_ns & 0x1);
  encoded++;

  *lenPtr = encoded - 1 - ((iei_present) ? 1 : 0);
  return encoded;
}

//------------------------------------------------------------------------------
// 10.5.5.28 Voice domain preference and UE's usage setting
//------------------------------------------------------------------------------
int decode_voice_domain_preference_and_ue_usage_setting(
    voice_domain_preference_and_ue_usage_setting_t
        *voicedomainpreferenceandueusagesetting,
    const bool iei_present, uint8_t *buffer, const uint32_t len) {
  int decoded = 0;
  uint8_t ielen = 0;

  if (iei_present) {
    CHECK_IEI_DECODER(GMM_VOICE_DOMAIN_PREFERENCE_AND_UE_USAGE_SETTING_IEI,
                      *buffer);
    decoded++;
  }

  memset(voicedomainpreferenceandueusagesetting, 0,
         sizeof(voice_domain_preference_and_ue_usage_setting_t));
  ielen = *(buffer + decoded);
  decoded++;
  CHECK_LENGTH_DECODER(len - decoded, ielen);
  voicedomainpreferenceandueusagesetting->ue_usage_setting =
      (*(buffer + decoded) >> 2) & 0x1;
  voicedomainpreferenceandueusagesetting->voice_domain_for_eutran =
      *(buffer + decoded) & 0x3;
  decoded++;
  return decoded;
}

//------------------------------------------------------------------------------
int encode_voice_domain_preference_and_ue_usage_setting(
    voice_domain_preference_and_ue_usage_setting_t
        *voicedomainpreferenceandueusagesetting,
    const bool iei_present, uint8_t *buffer, const uint32_t len) {
  uint8_t *lenPtr;
  uint32_t encoded = 0;

  /*
   * Checking IEI and pointer
   */
  CHECK_PDU_POINTER_AND_LENGTH_ENCODER(
      buffer, VOICE_DOMAIN_PREFERENCE_AND_UE_USAGE_SETTING_MINIMUM_LENGTH, len);

  if (iei_present) {
    *buffer = GMM_VOICE_DOMAIN_PREFERENCE_AND_UE_USAGE_SETTING_IEI;
    encoded++;
  }

  lenPtr = (buffer + encoded);
  encoded++;
  *(buffer + encoded) =
      0x00 | (voicedomainpreferenceandueusagesetting->ue_usage_setting << 2) |
      voicedomainpreferenceandueusagesetting->voice_domain_for_eutran;
  encoded++;
  *lenPtr = encoded - 1 - ((iei_present) ? 1 : 0);
  return encoded;
}
