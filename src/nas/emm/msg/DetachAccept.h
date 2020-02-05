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

#ifndef FILE_DETACH_ACCEPT_SEEN
#define FILE_DETACH_ACCEPT_SEEN

#include "3gpp_23.003.h"
#include "3gpp_24.007.h"
#include "3gpp_24.008.h"
#include "MessageType.h"
#include "SecurityHeaderType.h"

/* Minimum length macro. Formed by minimum length of each mandatory field */
#define DETACH_ACCEPT_MINIMUM_LENGTH (0)

/* Maximum length macro. Formed by maximum length of each field */
#define DETACH_ACCEPT_MAXIMUM_LENGTH (0)

/*
 * Message name: Detach accept
 * Description: This message is sent by the network to indicate that the detach
 * procedure has been completed. See table 8.2.10.1.1. Significance: dual
 * Direction: network to UE
 */

typedef struct detach_accept_msg_tag {
  /* Mandatory fields */
  eps_protocol_discriminator_t protocoldiscriminator : 4;
  security_header_type_t securityheadertype : 4;
  message_type_t messagetype;
} detach_accept_msg;

int decode_detach_accept(detach_accept_msg* detachaccept, uint8_t* buffer,
                         uint32_t len);

int encode_detach_accept(detach_accept_msg* detachaccept, uint8_t* buffer,
                         uint32_t len);

#endif /* ! defined(FILE_DETACH_ACCEPT_SEEN) */
