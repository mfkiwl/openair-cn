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

/*****************************************************************************

Source      emm_asDef.h

Version     0.1

Date        2012/10/16

Product     NAS stack

Subsystem   EPS Mobility Management

Author      Frederic Maurel

Description Defines the EMM primitives available at the EMMAS Service
        Access Point to transfer NAS messages to/from the Access
        Stratum sublayer.

*****************************************************************************/
#ifndef FILE_EMM_ASDEF_SEEN
#define FILE_EMM_ASDEF_SEEN
#include "3gpp_23.003.h"
#include "3gpp_36.401.h"
#include "TrackingAreaIdentityList.h"
#include "common_defs.h"
#include "common_types.h"
#include "emm_proc.h"
#include "securityDef.h"

/****************************************************************************/
/*********************  G L O B A L    C O N S T A N T S  *******************/
/****************************************************************************/

/*
 * EMMAS-SAP primitives
 */
typedef enum emm_as_primitive_u {
  _EMMAS_START = 200,
  _EMMAS_SECURITY_REQ,  /* EMM->AS: Security request          */
  _EMMAS_SECURITY_IND,  /* AS->EMM: Security indication       */
  _EMMAS_SECURITY_RES,  /* EMM->AS: Security response         */
  _EMMAS_SECURITY_REJ,  /* EMM->AS: Security reject           */
  _EMMAS_ESTABLISH_REQ, /* EMM->AS: Connection establish request  */
  _EMMAS_ESTABLISH_CNF, /* AS->EMM: Connection establish confirm  */
  _EMMAS_ESTABLISH_REJ, /* AS->EMM: Connection establish reject   */
  _EMMAS_RELEASE_REQ,   /* EMM->AS: Connection release request    */
  _EMMAS_RELEASE_IND,   /* AS->EMM: Connection release indication */
  _EMMAS_DATA_REQ,      /* EMM->AS: Data transfer request     */
  _EMMAS_DATA_IND,      /* AS->EMM: Data transfer indication      */
  _EMMAS_PAGE_IND,      /* AS->EMM: Paging data indication        */
  _EMMAS_STATUS_IND,    /* AS->EMM: Status indication         */

  _EMMAS_ERAB_SETUP_REQ,
  _EMMAS_ERAB_SETUP_CNF,
  _EMMAS_ERAB_SETUP_REJ,
  _EMMAS_ERAB_MODIFY_REQ,
  _EMMAS_ERAB_MODIFY_CNF,
  _EMMAS_ERAB_MODIFY_REJ,
  _EMMAS_ERAB_RELEASE_REQ,
  _EMMAS_ERAB_RELEASE_CNF,

  _EMMAS_END
} emm_as_primitive_t;

/* Data used to setup EPS NAS security */
typedef struct emm_as_security_data_s {
  bool is_new;                          /* New security data indicator      */
  ksi_t ksi;                            /* NAS key set identifier       */
  uint8_t sqn;                          /* Sequence number          */
  uint32_t count;                       /* NAS counter              */
  uint8_t knas_enc[AUTH_KNAS_ENC_SIZE]; /* NAS cyphering key               */
  uint8_t knas_int[AUTH_KNAS_INT_SIZE]; /* NAS integrity key               */
  bool is_knas_enc_present;
  bool is_knas_int_present;
} emm_as_security_data_t;

/****************************************************************************/
/************************  G L O B A L    T Y P E S  ************************/
/****************************************************************************/

/*
 * EMMAS primitive for security
 * ----------------------------
 */
typedef struct emm_as_security_s {
  int emm_cause;               /* EMM failure cause code       */
  mme_ue_s1ap_id_t ue_id;      /* UE lower layer identifier        */
  const guti_t* guti;          /* GUTI temporary mobile identity   */
  emm_as_security_data_t sctx; /* EPS NAS security context     */
  uint64_t puid;               // linked to procedure UID
  /*
   * Identity request/response
   */
  uint8_t ident_type; /* Type of requested UE's identity  */
  const imsi_t* imsi; /* The requested IMSI of the UE     */
  const imei_t* imei; /* The requested IMEI of the UE     */
  uint32_t tmsi;      /* The requested TMSI of the UE     */
  /*
   * Authentication request/response
   */
  ksi_t ksi;                    /* NAS key set identifier       */
  uint8_t rand[AUTH_RAND_SIZE]; /* Random challenge number      */
  uint8_t autn[AUTH_AUTN_SIZE]; /* Authentication token         */
  uint8_t res[AUTH_RES_SIZE];   /* Authentication response      */
  uint8_t auts[AUTH_AUTS_SIZE]; /* Synchronisation failure      */
  /*
   * Security Mode Command
   */
  uint8_t eea; /* Replayed EPS encryption algorithms   */
  uint8_t eia; /* Replayed EPS integrity algorithms    */
  uint8_t uea; /* Replayed UMTS encryption algorithms  */
  uint8_t ucs2;
  uint8_t uia; /* Replayed UMTS integrity algorithms   */
  uint8_t gea; /* Replayed GPRS encryption algorithms   */
  bool umts_present;
  bool gprs_present;
  bool imeisv_request;

  // Added by LG
  uint8_t selected_eea; /* Selected EPS encryption algorithms   */
  uint8_t selected_eia; /* Selected EPS integrity algorithms    */

#define EMM_AS_MSG_TYPE_IDENT 0x01 /* Identification message   */
#define EMM_AS_MSG_TYPE_AUTH 0x02  /* Authentication message   */
#define EMM_AS_MSG_TYPE_SMC 0x03   /* Security Mode Command    */
  uint8_t msg_type; /* Type of NAS security message to transfer */
} emm_as_security_t;

typedef struct emm_as_base_s {
  int emm_cause;          /* EMM failure cause code        */
  mme_ue_s1ap_id_t ue_id; /* UE lower layer identifier         */
} emm_as_base_t;
/*
 * EMMAS primitive for connection establishment
 * --------------------------------------------
 */
typedef struct emm_as_EPS_identity_s {
  const guti_t* guti;    /* The GUTI, if valid               */
  const tai_t* last_tai; /* The last visited registered Tracking
                          * Area Identity, if available          */
  const imsi_t* imsi;    /* IMSI in case of "AttachWithImsi"     */
  const imei_t* imei;    /* UE's IMEI for emergency bearer services  */
} emm_as_EPS_identity_t;

typedef struct emm_as_establish_s {
  int emm_cause;                /* EMM failure cause code        */
  mme_ue_s1ap_id_t ue_id;       /* UE lower layer identifier         */
  emm_as_EPS_identity_t eps_id; /* UE's EPS mobile identity      */
  guti_t* guti;                 /* TAU GUTI   */
  const guti_t* new_guti;       /* New GUTI, if re-allocated         */
  emm_as_security_data_t sctx;  /* EPS NAS security context      */
  uint8_t encryption : 4;       /* Ciphering algorithm           */
  uint8_t integrity : 4;        /* Integrity protection algorithm    */
  const plmn_t* plmn_id;        /* Identifier of the selected PLMN   */
  ecgi_t ecgi;      /* E-UTRAN CGI This information element is used to globally
                       identify a cell */
  const tai_t* tai; /* The first tracking area the UE is registered to */
  tai_list_t tai_list;                  /* Valid field if num tai > 0 */
  uint8_t* eps_network_feature_support; /* TAU Network feature support   */
  bool switch_off;                      /* true if the UE is switched off    */
  uint8_t type;                         /* Network attach/detach type        */
  uint8_t nas_info;                   /* Type of NAS information to transfer  */
  bstring nas_msg;                    /* NAS message to be transfered     */
  uint8_t eps_update_result;          /* TAU EPS update result   */
  uint16_t eps_bearer_context_status; /* TAU EPS bearer context result   */

  uint64_t puid;     /* linked to procedure UID */
  bool is_initial;   /* true if contained in initial message    */
  uint8_t rrc_cause; /* Connection establishment cause    */
  uint8_t rrc_type;  /* Associated call type          */
  ksi_t ksi;         /* NAS key set identifier        */
  int n_tacs;        /* Number of consecutive tracking areas
                      * the UE is registered to       */
  // tac_t                  tac;                         /* Code of the first
  // tracking area the UE
  //                                                     * is registered to */
#define EMM_AS_NAS_INFO_ATTACH 0x01     /* Attach request        */
#define EMM_AS_NAS_INFO_DETACH 0x02     /* Detach request        */
#define EMM_AS_NAS_INFO_TAU 0x03        /* Tracking Area Update request  */
#define EMM_AS_NAS_INFO_SR 0x04         /* Service Request       */
#define EMM_AS_NAS_INFO_EXTSR 0x05      /* Extended Service Request  */
#define EMM_AS_NAS_INFO_DETACH_REQ 0x06 /* Detach Request     */
#define EMM_AS_NAS_INFO_NONE 0xFF       /* No Nas Message  */

  uint32_t* t3412;                    /* GPRS T3412 timer   */
  void* location_area_identification; /* TAU Location area identification */
  // void                *ms_identity;                 /* TAU 8.2.26.7   MS
  // identity This IE may be included to assign or unassign a new TMSI to a UE
  // during a combined TA/LA update. */
  int* combined_tau_emm_cause;       /* TAU EMM failure cause code   */
  uint32_t* t3402;                   /* TAU GPRS T3402 timer   */
  uint32_t* t3423;                   /* TAU GPRS T3423 timer   */
  void* equivalent_plmns;            /* TAU Equivalent PLMNs   */
  void* emergency_number_list;       /* TAU Emergency number list   */
  uint8_t* additional_update_result; /* TAU Additional update result   */
  uint32_t* t3412_extended;          /* TAU GPRS timer   */
} emm_as_establish_t;

/*
 * EMMAS primitive for connection release
 * --------------------------------------
 */
typedef struct emm_as_release_s {
  int emm_cause;
  mme_ue_s1ap_id_t ue_id; /* UE lower layer identifier          */
  const guti_t* guti;     /* GUTI temporary mobile identity     */
#define EMM_AS_CAUSE_AUTHENTICATION 0x01 /* Authentication failure */
#define EMM_AS_CAUSE_DETACH 0x02         /* Detach requested   */
  uint8_t cause;                         /* Release cause */
} emm_as_release_t;

/*
 * EMMAS primitive for data transfer
 * ---------------------------------
 */
typedef struct emm_as_data_s {
  int emm_cause;                    /* EMM failure cause code        */
  mme_ue_s1ap_id_t ue_id;           /* UE lower layer identifier        */
  emm_as_EPS_identity_t eps_id;     /* UE's EPS mobile identity         */
  const guti_t* guti;               /* GUTI temporary mobile identity   */
  const guti_t* new_guti;           /* New GUTI, if re-allocated        */
  emm_as_security_data_t sctx_data; /* EPS NAS security context         */
  uint8_t encryption : 4;           /* Ciphering algorithm              */
  uint8_t integrity : 4;            /* Integrity protection algorithm   */
  const plmn_t* plmn_id;            /* Identifier of the selected PLMN  */
  ecgi_t ecgi;      /* E-UTRAN CGI This information element is used to globally
                       identify a cell */
  const tai_t* tai; /* Code of the first tracking area identity the UE is
                       registered to          */
  tai_list_t tai_list;                  /* Valid field if num tai > 0 */
  uint8_t* eps_network_feature_support; /* TAU Network feature support */
  bool switch_off;                      /* true if the UE is switched off   */
  uint8_t type;                         /* Network detach type          */
  uint8_t nas_info;                   /* Type of NAS information to transfer  */
  bstring nas_msg;                    /* NAS message to be transfered     */
  uint8_t eps_update_result;          /* TAU EPS update result   */
  uint16_t eps_bearer_context_status; /* EPS bearer context result   */

#define EMM_AS_DATA_DELIVERED_LOWER_LAYER_FAILURE 0
#define EMM_AS_DATA_DELIVERED_TRUE 1
#define EMM_AS_DATA_DELIVERED_LOWER_LAYER_NON_DELIVERY_INDICATION_DUE_TO_HO 2
  uint8_t delivered; /* Data message delivery indicator  */
  emm_proc_detach_type_t
      detach_type; /**< Set to true if reattach is required. */
  bool pending_deac;
#define EMM_AS_NAS_DATA_ATTACH 0x01        /* Attach complete      */
#define EMM_AS_NAS_DATA_DETACH_ACCEPT 0x02 /* Detach request       */
#define EMM_AS_NAS_DATA_TAU 0x03           /* TAU    Accept        */
#define EMM_AS_NAS_DATA_ATTACH_ACCEPT 0x04 /* Attach Accept        */
  /** MME initiated (implicit) Detach Request. */
#define EMM_AS_NAS_DATA_DETACH_REQUEST 0x06 /* Detach Request     */
} emm_as_data_t;

/*
 * EMMAS primitive for (dedicated) bearer establishment, modification and
 * removal
 * ----------------------------------------------------
 */

typedef struct emm_as_activate_bearer_context_req_s {
  int emm_cause;          /* EMM failure cause code        */
  mme_ue_s1ap_id_t ue_id; /* UE lower layer identifier        */
  ebi_t ebi;              /* EPS rab id                       */
  bool retry;
  int retx_count;
  bitrate_t mbr_dl;
  bitrate_t mbr_ul;
  bitrate_t gbr_dl;
  bitrate_t gbr_ul;
  emm_as_security_data_t sctx; /* EPS NAS security context         */
  bstring nas_msg;             /* NAS message to be transfered     */
} emm_as_activate_bearer_context_req_t;

typedef struct emm_as_modify_bearer_context_req_s {
  int emm_cause;          /* EMM failure cause code        */
  mme_ue_s1ap_id_t ue_id; /* UE lower layer identifier        */
  ebi_t ebi;              /* EPS rab id                       */
  bool retry;
  int retx_count;
  bitrate_t mbr_dl;
  bitrate_t mbr_ul;
  bitrate_t gbr_dl;
  bitrate_t gbr_ul;
  emm_as_security_data_t sctx; /* EPS NAS security context         */
  bstring nas_msg;             /* NAS message to be transfered     */
} emm_as_modify_bearer_context_req_t;

typedef struct emm_as_deactivate_bearer_context_req_s {
  int emm_cause;          /* EMM failure cause code        */
  mme_ue_s1ap_id_t ue_id; /* UE lower layer identifier        */
  ebi_t ebi; /* EPS erab ids. Some eNodeBs like Nokia for does not accept list
                of bearers for deactivation. */
  bool retry;
  int retx_count;
  emm_as_security_data_t sctx; /* EPS NAS security context         */
  bstring nas_msg;             /* NAS message to be transfered     */
} emm_as_deactivate_bearer_context_req_t;

typedef struct emm_as_erab_setup_rej_s {
  mme_ue_s1ap_id_t ue_id;
  ebi_t ebi;
} emm_as_erab_setup_rej_t;

typedef struct emm_as_erab_modify_rej_s {
  mme_ue_s1ap_id_t ue_id;
  ebi_t ebi;
  bool remove_bearer;
} emm_as_erab_modify_rej_t;

/*
 * EMMAS primitive for status indication
 * -------------------------------------
 */
typedef struct emm_as_status_s {
  int emm_cause;               /* EMM failure cause code        */
  mme_ue_s1ap_id_t ue_id;      /* UE lower layer identifier        */
  const guti_t* guti;          /* GUTI temporary mobile identity   */
  emm_as_security_data_t sctx; /* EPS NAS security context     */
} emm_as_status_t;

/*
 * EMMAS primitive for cell information
 * ------------------------------------
 */
typedef struct emm_as_cell_info_s {
  int emm_cause; /* EMM failure cause code        */
  mme_ue_s1ap_id_t
      ue_id; /* UE lower layer identifier        todo: define constant here?*/
  uint8_t found; /* Indicates whether a suitable cell is found   */
#define EMM_AS_PLMN_LIST_SIZE 6
  PLMN_LIST_T(EMM_AS_PLMN_LIST_SIZE) plmn_ids;
  /* List of identifiers of available PLMNs   */
  uint8_t rat;   /* Bitmap of Radio Access Technologies      */
  tac_t tac;     /* Tracking Area Code               */
  eci_t cell_id; /* cell identity                */
} emm_as_cell_info_t;

/*
 * --------------------------------
 * Structure of EMMAS-SAP primitive
 * --------------------------------
 */
typedef struct emm_as_s {
  emm_as_primitive_t primitive;
  union {
    emm_as_base_t base; /* EMM failure cause code        */
    emm_as_security_t security;
    emm_as_establish_t establish;
    emm_as_release_t release;
    emm_as_data_t data;
    emm_as_activate_bearer_context_req_t activate_bearer_context_req;
    emm_as_modify_bearer_context_req_t modify_bearer_context_req;
    emm_as_deactivate_bearer_context_req_t deactivate_bearer_context_req;
    emm_as_erab_setup_rej_t erab_setup_rej;
    emm_as_erab_modify_rej_t erab_modify_rej;
    emm_as_status_t status;
    emm_as_cell_info_t cell_info;
  } u;
} emm_as_t;

/****************************************************************************/
/********************  G L O B A L    V A R I A B L E S  ********************/
/****************************************************************************/

/****************************************************************************/
/******************  E X P O R T E D    F U N C T I O N S  ******************/
/****************************************************************************/

/*
 * Defined in LowerLayer.c
 * Setup security data according to the given EPS security context
 */
void emm_as_set_security_data(emm_as_security_data_t* data, const void* context,
                              bool is_new, bool is_ciphered);

#endif /* FILE_EMM_ASDEF_SEEN*/
