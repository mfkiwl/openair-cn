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

/*! \file mcc_mnc_itu.c
  \brief
  \author Lionel Gauthier
  \company Eurecom
  \email: lionel.gauthier@eurecom.fr
*/

#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "assertions.h"
#include "mcc_mnc_itu.h"

// From http://www.itu.int/pub/T-SP-E.212B-2014
const mcc_mnc_list_t mcc_mnc_list[] = {
    {001, "01"},  {412, "01"},  {412, "20"},  {412, "40"},
    {412, "50"},  {412, "80"},  {412, "88"},  {276, "01"},
    {276, "02"},  {276, "03"},  {276, "04"},  {603, "01"},
    {603, "02"},  {262, "01"},  {262, "02"},  {262, "03"},
    {262, "04"},  {262, "05"},  {262, "06"},  {262, "07"},
    {262, "08"},  {262, "09"},  {262, "10"},  {262, "11"},
    {262, "12"},  {262, "13"},  {262, "14"},  {262, "15"},
    {262, "16"},  {262, "17"},  {262, "18"},  {262, "19"},
    {262, "20"},  {262, "41"},  {262, "42"},  {262, "43"},
    {262, "77"},  {262, "78"},  {262, "79"},  {213, "03"},
    {631, "02"},  {631, "04"},  {365, "010"}, {365, "840"},
    {344, "030"}, {344, "920"}, {344, "930"}, {420, "01"},
    {420, "03"},  {722, "010"}, {722, "020"}, {722, "070"},
    {722, "310"}, {722, "320"}, {722, "330"}, {722, "341"},
    {363, "01"},  {505, "01"},  {505, "02"},  {505, "03"},
    {505, "04"},  {505, "05"},  {505, "06"},  {505, "07"},
    {505, "08"},  {505, "09"},  {505, "10"},  {505, "11"},
    {505, "12"},  {505, "13"},  {505, "14"},  {505, "15"},
    {505, "16"},  {505, "17"},  {505, "18"},  {505, "19"},
    {505, "20"},  {505, "21"},  {505, "22"},  {505, "23"},
    {505, "24"},  {505, "25"},  {505, "26"},  {505, "27"},
    {505, "28"},  {505, "30"},  {505, "31"},  {505, "62"},
    {505, "68"},  {505, "71"},  {505, "72"},  {505, "88"},
    {505, "90"},  {505, "99"},  {232, "01"},  {232, "02"},
    {232, "03"},  {232, "04"},  {232, "05"},  {232, "06"},
    {232, "07"},  {232, "09"},  {232, "10"},  {232, "11"},
    {232, "12"},  {232, "14"},  {232, "15"},  {232, "91"},
    {400, "01"},  {400, "02"},  {400, "03"},  {400, "04"},
    {426, "01"},  {426, "02"},  {426, "03"},  {426, "04"},
    {426, "05"},  {470, "01"},  {470, "02"},  {470, "03"},
    {342, "600"}, {342, "820"}, {257, "01"},  {257, "02"},
    {257, "03"},  {257, "04"},  {257, "05"},  {257, "06"},
    {206, "01"},  {206, "02"},  {206, "05"},  {206, "06"},
    {206, "07"},  {206, "10"},  {206, "20"},  {702, "67"},
    {702, "68"},  {616, "01"},  {616, "02"},  {616, "03"},
    {350, "000"}, {402, "11"},  {402, "17"},  {736, "01"},
    {736, "02"},  {736, "03"},  {218, "03"},  {218, "05"},
    {218, "90"},  {652, "01"},  {652, "02"},  {652, "04"},
    {724, "00"},  {724, "01"},  {724, "02"},  {724, "03"},
    {724, "04"},  {724, "05"},  {724, "06"},  {724, "10"},
    {724, "11"},  {724, "15"},  {724, "16"},  {724, "18"},
    {724, "23"},  {724, "24"},  {724, "30"},  {724, "31"},
    {724, "32"},  {724, "33"},  {724, "34"},  {724, "35"},
    {724, "36"},  {724, "37"},  {724, "38"},  {724, "39"},
    {724, "54"},  {724, "99"},  {528, "11"},  {284, "01"},
    {284, "05"},  {613, "02"},  {613, "03"},  {642, "01"},
    {642, "02"},  {642, "03"},  {642, "07"},  {642, "82"},
    {625, "01"},  {625, "02"},  {456, "01"},  {456, "02"},
    {456, "03"},  {456, "04"},  {456, "05"},  {456, "06"},
    {456, "08"},  {456, "18"},  {624, "01"},  {624, "02"},
    {302, "220"}, {302, "221"}, {302, "222"}, {302, "250"},
    {302, "270"}, {302, "290"}, {302, "320"}, {302, "340"},
    {302, "360"}, {302, "370"}, {302, "380"}, {302, "390"},
    {302, "490"}, {302, "500"}, {302, "510"}, {302, "530"},
    {302, "560"}, {302, "570"}, {302, "590"}, {302, "610"},
    {302, "620"}, {302, "630"}, {302, "640"}, {302, "656"},
    {302, "660"}, {302, "670"}, {302, "680"}, {302, "690"},
    {302, "710"}, {302, "720"}, {302, "730"}, {302, "740"},
    {302, "760"}, {302, "770"}, {302, "780"}, {302, "860"},
    {302, "880"}, {302, "940"}, {302, "990"}, {346, "140"},
    {623, "01"},  {623, "02"},  {623, "03"},  {730, "01"},
    {730, "02"},  {730, "03"},  {730, "04"},  {730, "05"},
    {730, "06"},  {730, "07"},  {730, "08"},  {730, "09"},
    {730, "10"},  {730, "11"},  {730, "12"},  {730, "13"},
    {730, "14"},  {730, "15"},  {460, "00"},  {460, "01"},
    {460, "03"},  {460, "04"},  {280, "01"},  {280, "10"},
    {280, "20"},  {280, "22"},  {732, "001"}, {732, "002"},
    {732, "020"}, {732, "099"}, {732, "101"}, {732, "102"},
    {732, "103"}, {732, "111"}, {732, "123"}, {732, "130"},
    {654, "01"},  {629, "01"},  {629, "10"},  {548, "01"},
    {450, "02"},  {450, "03"},  {450, "06"},  {712, "01"},
    {712, "02"},  {712, "03"},  {712, "04"},  {712, "20"},
    {612, "02"},  {612, "03"},  {612, "04"},  {612, "05"},
    {612, "06"},  {612, "07"},  {219, "01"},  {219, "02"},
    {219, "10"},  {368, "01"},  {362, "51"},  {362, "69"},
    {362, "91"},  {238, "01"},  {238, "02"},  {238, "03"},
    {238, "04"},  {238, "06"},  {238, "08"},  {238, "10"},
    {238, "12"},  {238, "13"},  {238, "20"},  {238, "28"},
    {238, "30"},  {238, "43"},  {238, "66"},  {238, "77"},
    {638, "01"},  {370, "01"},  {370, "02"},  {370, "03"},
    {370, "04"},  {366, "110"}, {602, "01"},  {602, "02"},
    {602, "03"},  {706, "01"},  {706, "02"},  {706, "03"},
    {424, "02"},  {740, "00"},  {740, "01"},  {740, "02"},
    {214, "01"},  {214, "03"},  {214, "04"},  {214, "05"},
    {214, "06"},  {214, "07"},  {214, "08"},  {214, "09"},
    {214, "10"},  {214, "11"},  {214, "12"},  {214, "13"},
    {214, "14"},  {214, "15"},  {214, "16"},  {214, "17"},
    {214, "18"},  {214, "19"},  {214, "20"},  {214, "21"},
    {214, "22"},  {214, "24"},  {214, "25"},  {214, "26"},
    {214, "27"},  {214, "28"},  {214, "29"},  {214, "30"},
    {214, "31"},  {214, "32"},  {248, "01"},  {248, "02"},
    {248, "03"},  {248, "04"},  {248, "05"},  {248, "06"},
    {248, "07"},  {248, "08"},  {248, "09"},  {248, "71"},
    {310, "010"}, {310, "012"}, {310, "013"}, {310, "016"},
    {310, "017"}, {310, "020"}, {310, "028"},  // NON ITU, ADDED BY EURECOM
    {310, "030"}, {310, "035"}, {310, "040"}, {310, "050"},
    {310, "060"}, {310, "070"}, {310, "080"}, {310, "090"},
    {310, "100"}, {310, "110"}, {310, "120"}, {310, "130"},
    {310, "140"}, {310, "150"}, {310, "160"}, {310, "170"},
    {310, "180"}, {310, "190"}, {310, "200"}, {310, "210"},
    {310, "220"}, {310, "230"}, {310, "240"}, {310, "250"},
    {310, "260"}, {310, "270"}, {310, "280"}, {310, "290"},
    {310, "300"}, {310, "310"}, {310, "320"}, {310, "330"},
    {310, "340"}, {310, "350"}, {310, "360"}, {310, "370"},
    {310, "380"}, {310, "390"}, {310, "400"}, {310, "410"},
    {310, "420"}, {310, "430"}, {310, "440"}, {310, "450"},
    {310, "460"}, {310, "470"}, {310, "480"}, {310, "490"},
    {310, "500"}, {310, "510"}, {310, "520"}, {310, "530"},
    {310, "540"}, {310, "550"}, {310, "560"}, {310, "570"},
    {310, "580"}, {310, "590"}, {310, "600"}, {310, "610"},
    {310, "620"}, {310, "640"}, {310, "650"}, {310, "660"},
    {310, "670"}, {310, "680"}, {310, "690"}, {310, "700"},
    {310, "710"}, {310, "720"}, {310, "730"}, {310, "740"},
    {310, "750"}, {310, "760"}, {310, "770"}, {310, "780"},
    {310, "790"}, {310, "800"}, {310, "810"}, {310, "820"},
    {310, "830"}, {310, "840"}, {310, "850"}, {310, "860"},
    {310, "870"}, {310, "880"}, {310, "890"}, {310, "900"},
    {310, "910"}, {310, "920"}, {310, "930"}, {310, "940"},
    {310, "950"}, {310, "960"}, {310, "970"}, {310, "980"},
    {310, "990"}, {311, "000"}, {311, "010"}, {311, "020"},
    {311, "030"}, {311, "040"}, {311, "050"}, {311, "060"},
    {311, "070"}, {311, "080"}, {311, "090"}, {311, "100"},
    {311, "110"}, {311, "120"}, {311, "130"}, {311, "140"},
    {311, "150"}, {311, "160"}, {311, "170"}, {311, "180"},
    {311, "190"}, {311, "200"}, {311, "210"}, {311, "220"},
    {311, "230"}, {311, "240"}, {311, "250"}, {311, "260"},
    {311, "270"}, {311, "271"}, {311, "272"}, {311, "273"},
    {311, "274"}, {311, "275"}, {311, "276"}, {311, "277"},
    {311, "278"}, {311, "279"}, {311, "280"}, {311, "281"},
    {311, "282"}, {311, "283"}, {311, "284"}, {311, "285"},
    {311, "286"}, {311, "287"}, {311, "288"}, {311, "289"},
    {311, "290"}, {311, "300"}, {311, "310"}, {311, "320"},
    {311, "330"}, {311, "340"}, {311, "350"}, {311, "360"},
    {311, "370"}, {311, "380"}, {311, "390"}, {311, "410"},
    {311, "420"}, {311, "430"}, {311, "440"}, {311, "450"},
    {311, "460"}, {311, "470"}, {311, "480"}, {311, "481"},
    {311, "482"}, {311, "483"}, {311, "484"}, {311, "485"},
    {311, "486"}, {311, "487"}, {311, "488"}, {311, "489"},
    {311, "490"}, {311, "500"}, {311, "510"}, {311, "520"},
    {311, "530"}, {311, "540"}, {311, "550"}, {311, "560"},
    {311, "570"}, {311, "580"}, {311, "590"}, {311, "600"},
    {311, "610"}, {311, "620"}, {311, "630"}, {311, "640"},
    {311, "650"}, {311, "660"}, {311, "670"}, {311, "680"},
    {311, "690"}, {311, "700"}, {311, "710"}, {311, "720"},
    {311, "730"}, {311, "740"}, {311, "750"}, {311, "760"},
    {311, "770"}, {311, "800"}, {311, "810"}, {311, "820"},
    {311, "830"}, {311, "840"}, {311, "850"}, {311, "860"},
    {311, "870"}, {311, "880"}, {311, "890"}, {311, "900"},
    {311, "910"}, {311, "920"}, {311, "940"}, {311, "950"},
    {311, "960"}, {311, "970"}, {311, "980"}, {311, "990"},
    {312, "010"}, {312, "020"}, {312, "030"}, {312, "040"},
    {312, "050"}, {312, "060"}, {312, "070"}, {312, "080"},
    {312, "090"}, {312, "100"}, {312, "110"}, {312, "120"},
    {312, "130"}, {312, "140"}, {312, "150"}, {312, "160"},
    {312, "170"}, {312, "180"}, {312, "190"}, {312, "200"},
    {313, "100"}, {316, "010"}, {316, "011"}, {636, "01"},
    {750, "001"}, {250, "01"},  {250, "02"},  {250, "03"},
    {250, "04"},  {250, "05"},  {250, "07"},  {250, "10"},
    {250, "11"},  {250, "12"},  {250, "13"},  {250, "16"},
    {250, "17"},  {250, "19"},  {250, "20"},  {250, "28"},
    {250, "39"},  {250, "44"},  {250, "92"},  {250, "93"},
    {250, "99"},  {274, "02"},  {288, "01"},  {288, "02"},
    {542, "01"},  {542, "02"},  {542, "03"},  {244, "03"},
    {244, "04"},  {244, "05"},  {244, "09"},  {244, "10"},
    {244, "12"},  {244, "13"},  {244, "14"},  {244, "16"},
    {244, "21"},  {244, "29"},  {244, "91"},  {208, "01"},
    {208, "02"},  {208, "03"},  {208, "04"},  {208, "05"},
    {208, "06"},  {208, "07"},  {208, "09"},  {208, "10"},
    {208, "11"},  {208, "13"},  {208, "14"},  {208, "15"},
    {208, "20"},  {208, "21"},  {208, "22"},  {208, "23"},
    {208, "24"},  {208, "25"},  {208, "26"},  {208, "27"},
    {208, "28"},  {208, "29"},  {208, "30"},  {208, "31"},
    {208, "34"},  // NON ITU, ADDED BY EURECOM
    {208, "88"},  {208, "89"},  {208, "90"},  {208, "91"},
    {208, "92"},  // NON ITU, ADDED BY EURECOM
    {208, "93"},  // NON ITU, ADDED BY EURECOM
    {208, "94"},  // NON ITU, ADDED BY EURECOM
    {208, "95"},  // NON ITU, ADDED BY EURECOM
    {208, "96"},  // NON ITU, ADDED BY EURECOM
    {208, "97"},  // NON ITU, ADDED BY EURECOM
    {208, "98"},  // NON ITU, ADDED BY EURECOM
    {208, "99"},  // NON ITU, ADDED BY EURECOM
    {647, "00"},  {647, "02"},  {647, "10"},  {628, "01"},
    {628, "02"},  {628, "03"},  {628, "04"},  {628, "05"},
    {607, "01"},  {607, "02"},  {607, "03"},  {607, "04"},
    {282, "01"},  {282, "02"},  {282, "03"},  {282, "04"},
    {282, "05"},  {282, "06"},  {282, "07"},  {620, "01"},
    {620, "02"},  {620, "03"},  {620, "04"},  {620, "11"},
    {266, "01"},  {266, "09"},  {202, "01"},  {202, "02"},
    {202, "03"},  {202, "04"},  {202, "05"},  {202, "06"},
    {202, "07"},  {202, "09"},  {202, "10"},  {352, "110"},
    {290, "01"},  {340, "01"},  {340, "02"},  {340, "03"},
    {340, "08"},  {340, "10"},  {340, "20"},  {704, "01"},
    {704, "02"},  {704, "03"},  {611, "01"},  {611, "02"},
    {611, "05"},  {627, "01"},  {632, "01"},  {632, "02"},
    {738, "002"}, {738, "01"},  {340, "11"},  {372, "01"},
    {372, "02"},  {372, "03"},  {708, "001"}, {708, "002"},
    {708, "040"}, {454, "00"},  {454, "01"},  {454, "02"},
    {454, "03"},  {454, "04"},  {454, "05"},  {454, "06"},
    {454, "07"},  {454, "08"},  {454, "09"},  {454, "10"},
    {454, "11"},  {454, "12"},  {454, "15"},  {454, "16"},
    {454, "18"},  {454, "19"},  {454, "2X"},  {454, "3X"},
    {216, "01"},  {216, "30"},  {216, "70"},  {216, "71"},
    {404, "00"},  {404, "01"},  {404, "02"},  {404, "03"},
    {404, "04"},  {404, "05"},  {404, "06"},  {404, "07"},
    {404, "09"},  {404, "10"},  {404, "11"},  {404, "12"},
    {404, "13"},  {404, "14"},  {404, "15"},  {404, "16"},
    {404, "17"},  {404, "18"},  {404, "19"},  {404, "20"},
    {404, "21"},  {404, "22"},  {404, "23"},  {404, "24"},
    {404, "25"},  {404, "27"},  {404, "29"},  {404, "30"},
    {404, "31"},  {404, "33"},  {404, "34"},  {404, "35"},
    {404, "36"},  {404, "37"},  {404, "38"},  {404, "40"},
    {404, "41"},  {404, "42"},  {404, "43"},  {404, "44"},
    {404, "46"},  {404, "48"},  {404, "49"},  {404, "50"},
    {404, "51"},  {404, "52"},  {404, "53"},  {404, "54"},
    {404, "55"},  {404, "56"},  {404, "57"},  {404, "58"},
    {404, "59"},  {404, "60"},  {404, "61"},  {404, "62"},
    {404, "63"},  {404, "64"},  {404, "65"},  {404, "66"},
    {404, "67"},  {404, "68"},  {404, "69"},  {404, "70"},
    {404, "71"},  {404, "72"},  {404, "73"},  {404, "74"},
    {404, "75"},  {404, "76"},  {404, "77"},  {404, "78"},
    {404, "79"},  {404, "80"},  {404, "81"},  {404, "82"},
    {404, "83"},  {404, "84"},  {404, "85"},  {404, "86"},
    {404, "87"},  {404, "88"},  {404, "89"},  {404, "90"},
    {404, "91"},  {404, "92"},  {404, "93"},  {404, "94"},
    {404, "95"},  {404, "96"},  {404, "97"},  {404, "98"},
    {404, "99"},  {405, "000"}, {405, "005"}, {405, "006"},
    {405, "007"}, {405, "009"}, {405, "010"}, {405, "011"},
    {405, "012"}, {405, "013"}, {405, "014"}, {405, "018"},
    {405, "020"}, {405, "021"}, {405, "022"}, {405, "025"},
    {405, "027"}, {405, "029"}, {405, "030"}, {405, "031"},
    {405, "032"}, {405, "033"}, {405, "034"}, {405, "035"},
    {405, "036"}, {405, "037"}, {405, "038"}, {405, "039"},
    {405, "040"}, {405, "041"}, {405, "042"}, {405, "043"},
    {405, "044"}, {405, "045"}, {405, "046"}, {405, "047"},
    {405, "08"},  {405, "12"},  {405, "15"},  {405, "17"},
    {405, "23"},  {405, "28"},  {405, "52"},  {405, "53"},
    {405, "54"},  {405, "55"},  {405, "56"},  {405, "66"},
    {405, "67"},  {405, "68"},  {405, "70"},  {405, "71"},
    {405, "72"},  {405, "73"},  {405, "74"},  {405, "750"},
    {405, "751"}, {405, "752"}, {405, "753"}, {405, "754"},
    {405, "755"}, {405, "76"},  {405, "77"},  {405, "799"},
    {405, "800"}, {405, "801"}, {405, "802"}, {405, "803"},
    {405, "804"}, {405, "805"}, {405, "806"}, {405, "807"},
    {405, "808"}, {405, "809"}, {405, "81"},  {405, "82"},
    {405, "83"},  {405, "84"},  {405, "85"},  {405, "86"},
    {510, "00"},  {510, "01"},  {510, "08"},  {510, "10"},
    {510, "11"},  {510, "21"},  {510, "28"},  {432, "11"},
    {432, "14"},  {432, "19"},  {418, "05"},  {418, "20"},
    {418, "30"},  {418, "40"},  {418, "47"},  {418, "48"},
    {418, "49"},  {418, "62"},  {418, "70"},  {418, "80"},
    {418, "81"},  {418, "83"},  {418, "84"},  {418, "85"},
    {418, "86"},  {418, "87"},  {418, "88"},  {418, "89"},
    {418, "91"},  {418, "92"},  {418, "93"},  {418, "94"},
    {272, "01"},  {272, "02"},  {272, "03"},  {272, "07"},
    {272, "09"},  {274, "01"},  {274, "02"},  {274, "03"},
    {274, "04"},  {274, "07"},  {425, "01"},  {425, "02"},
    {425, "03"},  {425, "04"},  {425, "06"},  {425, "07"},
    {425, "08"},  {425, "11"},  {425, "12"},  {425, "13"},
    {425, "14"},  {425, "15"},  {425, "16"},  {425, "17"},
    {425, "18"},  {425, "19"},  {425, "20"},  {425, "21"},
    {222, "01"},  {222, "02"},  {222, "10"},  {222, "77"},
    {222, "88"},  {222, "98"},  {222, "99"},  {338, "020"},
    {338, "050"}, {338, "110"}, {440, "01"},  {440, "02"},
    {440, "03"},  {440, "04"},  {440, "06"},  {440, "07"},
    {440, "08"},  {440, "09"},  {440, "10"},  {440, "11"},
    {440, "12"},  {440, "13"},  {440, "14"},  {440, "15"},
    {440, "16"},  {440, "17"},  {440, "18"},  {440, "19"},
    {440, "20"},  {440, "21"},  {440, "22"},  {440, "23"},
    {440, "24"},  {440, "25"},  {440, "26"},  {440, "27"},
    {440, "28"},  {440, "29"},  {440, "30"},  {440, "31"},
    {440, "32"},  {440, "33"},  {440, "34"},  {440, "35"},
    {440, "36"},  {440, "37"},  {440, "38"},  {440, "39"},
    {440, "40"},  {440, "41"},  {440, "42"},  {440, "43"},
    {440, "44"},  {440, "45"},  {440, "46"},  {440, "47"},
    {440, "48"},  {440, "49"},  {440, "50"},  {440, "51"},
    {440, "52"},  {440, "53"},  {440, "54"},  {440, "55"},
    {440, "56"},  {440, "58"},  {440, "60"},  {440, "61"},
    {440, "62"},  {440, "63"},  {440, "64"},  {440, "65"},
    {440, "66"},  {440, "67"},  {440, "68"},  {440, "69"},
    {440, "70"},  {440, "71"},  {440, "72"},  {440, "73"},
    {440, "74"},  {440, "75"},  {440, "76"},  {440, "77"},
    {440, "78"},  {440, "79"},  {440, "80"},  {440, "81"},
    {440, "82"},  {440, "83"},  {440, "84"},  {440, "85"},
    {440, "86"},  {440, "87"},  {440, "88"},  {440, "89"},
    {440, "90"},  {440, "92"},  {440, "93"},  {440, "94"},
    {440, "95"},  {440, "96"},  {440, "97"},  {440, "98"},
    {440, "99"},  {441, "40"},  {441, "41"},  {441, "42"},
    {441, "43"},  {441, "44"},  {441, "45"},  {441, "50"},
    {441, "51"},  {441, "61"},  {441, "62"},  {441, "63"},
    {441, "64"},  {441, "65"},  {441, "70"},  {441, "90"},
    {441, "91"},  {441, "92"},  {441, "93"},  {441, "94"},
    {441, "98"},  {441, "99"},  {416, "01"},  {416, "02"},
    {416, "03"},  {416, "77"},  {401, "01"},  {401, "02"},
    {639, "02"},  {639, "03"},  {437, "01"},  {419, "02"},
    {419, "03"},  {419, "04"},  {457, "01"},  {457, "02"},
    {457, "08"},  {651, "01"},  {651, "02"},  {247, "01"},
    {247, "02"},  {247, "03"},  {247, "04"},  {247, "05"},
    {247, "06"},  {247, "07"},  {247, "08"},  {247, "09"},
    {294, "01"},  {294, "02"},  {294, "03"},  {294, "10"},
    {294, "11"},  {415, "05"},  {415, "32"},  {415, "33"},
    {415, "34"},  {415, "35"},  {415, "36"},  {415, "37"},
    {415, "38"},  {415, "39"},  {618, "04"},  {228, "01"},
    {295, "01"},  {295, "02"},  {295, "05"},  {295, "06"},
    {246, "01"},  {246, "02"},  {246, "03"},  {270, "01"},
    {270, "02"},  {270, "10"},  {270, "77"},  {270, "78"},
    {270, "99"},  {455, "00"},  {455, "01"},  {455, "02"},
    {455, "03"},  {455, "04"},  {455, "05"},  {455, "06"},
    {646, "01"},  {646, "02"},  {646, "04"},  {502, "10"},
    {502, "11"},  {502, "12"},  {502, "13"},  {502, "14"},
    {502, "16"},  {502, "17"},  {502, "18"},  {502, "19"},
    {502, "20"},  {650, "01"},  {650, "10"},  {472, "01"},
    {610, "01"},  {278, "01"},  {278, "21"},  {278, "77"},
    {604, "00"},  {604, "01"},  {340, "12"},  {617, "01"},
    {617, "02"},  {617, "03"},  {617, "10"},  {609, "01"},
    {609, "02"},  {609, "10"},  {334, "001"}, {334, "010"},
    {334, "020"}, {334, "030"}, {334, "040"}, {334, "050"},
    {334, "060"}, {334, "066"}, {334, "070"}, {334, "080"},
    {334, "090"}, {550, "01"},  {259, "01"},  {259, "02"},
    {259, "04"},  {259, "05"},  {259, "99"},  {428, "99"},
    {297, "01"},  {297, "02"},  {297, "03"},  {354, "860"},
    {643, "01"},  {643, "03"},  {643, "04"},  {414, "01"},
    {649, "01"},  {649, "02"},  {649, "03"},  {542, "02"},
    {429, "01"},  {710, "21"},  {710, "73"},  {614, "01"},
    {614, "02"},  {614, "03"},  {621, "20"},  {621, "30"},
    {621, "40"},  {621, "50"},  {621, "60"},  {555, "01"},
    {242, "01"},  {242, "02"},  {242, "03"},  {242, "04"},
    {242, "05"},  {242, "07"},  {242, "08"},  {242, "09"},
    {242, "10"},  {242, "11"},  {242, "12"},  {242, "20"},
    {242, "21"},  {242, "22"},  {242, "23"},  {242, "24"},
    {546, "01"},  {530, "00"},  {530, "01"},  {530, "02"},
    {530, "03"},  {530, "04"},  {530, "05"},  {530, "06"},
    {530, "07"},  {530, "24"},  {422, "02"},  {422, "03"},
    {422, "04"},  {641, "01"},  {641, "10"},  {641, "11"},
    {641, "14"},  {641, "18"},  {641, "22"},  {641, "30"},
    {641, "33"},  {641, "40"},  {641, "44"},  {641, "66"},
    {434, "01"},  {434, "02"},  {434, "04"},  {434, "05"},
    {434, "07"},  {410, "01"},  {410, "03"},  {410, "04"},
    {410, "06"},  {410, "07"},  {552, "01"},  {714, "01"},
    {714, "02"},  {714, "020"}, {714, "03"},  {714, "04"},
    {537, "01"},  {537, "02"},  {537, "03"},  {744, "01"},
    {744, "02"},  {744, "03"},  {204, "01"},  {204, "02"},
    {204, "03"},  {204, "04"},  {204, "05"},  {204, "06"},
    {204, "07"},  {204, "08"},  {204, "09"},  {204, "10"},
    {204, "12"},  {204, "13"},  {204, "15"},  {204, "16"},
    {204, "17"},  {204, "18"},  {204, "19"},  {204, "20"},
    {204, "21"},  {204, "22"},  {204, "23"},  {204, "24"},
    {204, "25"},  {204, "26"},  {204, "28"},  {204, "29"},
    {204, "60"},  {204, "61"},  {204, "64"},  {204, "65"},
    {204, "66"},  {204, "67"},  {204, "68"},  {204, "69"},
    {716, "10"},  {515, "01"},  {515, "02"},  {515, "03"},
    {515, "05"},  {260, "01"},  {260, "02"},  {260, "03"},
    {260, "04"},  {260, "05"},  {260, "06"},  {260, "07"},
    {260, "08"},  {260, "09"},  {260, "10"},  {260, "11"},
    {260, "12"},  {260, "13"},  {260, "14"},  {260, "15"},
    {260, "16"},  {260, "17"},  {260, "18"},  {260, "19"},
    {260, "20"},  {260, "21"},  {260, "22"},  {260, "23"},
    {260, "24"},  {260, "25"},  {260, "26"},  {260, "27"},
    {260, "28"},  {260, "29"},  {260, "30"},  {260, "31"},
    {260, "32"},  {260, "33"},  {260, "34"},  {260, "98"},
    {547, "10"},  {547, "15"},  {547, "20"},  {268, "01"},
    {268, "03"},  {268, "05"},  {268, "06"},  {427, "01"},
    {427, "06"},  {630, "01"},  {630, "02"},  {630, "05"},
    {630, "86"},  {630, "88"},  {630, "89"},  {630, "90"},
    {230, "01"},  {230, "02"},  {230, "03"},  {230, "04"},
    {230, "05"},  {230, "07"},  {230, "08"},  {230, "98"},
    {417, "01"},  {417, "02"},  {417, "09"},  {226, "01"},
    {226, "02"},  {226, "03"},  {226, "04"},  {226, "05"},
    {226, "06"},  {226, "10"},  {226, "11"},  {234, "00"},
    {234, "01"},  {234, "02"},  {234, "03"},  {234, "04"},
    {234, "05"},  {234, "06"},  {234, "07"},  {234, "08"},
    {234, "09"},  {234, "10"},  {234, "11"},  {234, "12"},
    {234, "13"},  {234, "14"},  {234, "15"},  {234, "16"},
    {234, "17"},  {234, "18"},  {234, "19"},  {234, "20"},
    {234, "21"},  {234, "22"},  {234, "23"},  {234, "24"},
    {234, "25"},  {234, "26"},  {234, "27"},  {234, "28"},
    {234, "29"},  {234, "30"},  {234, "31"},  {234, "32"},
    {234, "33"},  {234, "34"},  {234, "35"},  {234, "36"},
    {234, "37"},  {234, "38"},  {234, "39"},  {234, "50"},
    {234, "51"},  {234, "52"},  {234, "53"},  {234, "55"},
    {234, "58"},  {234, "76"},  {234, "78"},  {234, "86"},
    {235, "00"},  {235, "01"},  {235, "02"},  {235, "77"},
    {235, "91"},  {235, "92"},  {235, "94"},  {235, "95"},
    {635, "10"},  {635, "13"},  {635, "14"},  {635, "17"},
    {358, "110"}, {356, "110"}, {292, "01"},  {308, "01"},
    {360, "110"}, {540, "02"},  {549, "01"},  {549, "27"},
    {626, "01"},  {608, "01"},  {608, "02"},  {608, "03"},
    {608, "04"},  {220, "01"},  {220, "03"},  {220, "05"},
    {633, "01"},  {633, "02"},  {633, "10"},  {619, "01"},
    {619, "02"},  {619, "03"},  {619, "04"},  {619, "05"},
    {619, "25"},  {619, "40"},  {619, "50"},  {525, "01"},
    {525, "02"},  {525, "03"},  {525, "05"},  {525, "12"},
    {231, "01"},  {231, "02"},  {231, "04"},  {231, "05"},
    {293, "40"},  {293, "41"},  {293, "64"},  {293, "70"},
    {634, "01"},  {634, "02"},  {634, "05"},  {634, "06"},
    {634, "99"},  {413, "02"},  {413, "03"},  {659, "12"},
    {659, "91"},  {659, "92"},  {659, "95"},  {659, "97"},
    {655, "01"},  {655, "02"},  {655, "04"},  {655, "06"},
    {655, "07"},  {655, "10"},  {655, "11"},  {655, "12"},
    {655, "13"},  {655, "14"},  {655, "19"},  {655, "21"},
    {655, "25"},  {655, "27"},  {655, "30"},  {655, "31"},
    {655, "32"},  {655, "33"},  {655, "34"},  {655, "35"},
    {655, "36"},  {655, "41"},  {655, "50"},  {655, "51"},
    {240, "01"},  {240, "02"},  {240, "03"},  {240, "04"},
    {240, "05"},  {240, "06"},  {240, "08"},  {240, "10"},
    {240, "12"},  {240, "13"},  {240, "14"},  {240, "15"},
    {240, "16"},  {240, "17"},  {240, "18"},  {240, "19"},
    {240, "20"},  {240, "21"},  {240, "22"},  {240, "23"},
    {240, "24"},  {240, "26"},  {240, "27"},  {240, "28"},
    {240, "29"},  {240, "30"},  {240, "32"},  {240, "33"},
    {240, "34"},  {240, "35"},  {240, "36"},  {240, "37"},
    {240, "38"},  {240, "40"},  {240, "41"},  {240, "42"},
    {240, "43"},  {240, "44"},  {240, "45"},  {240, "65"},
    {240, "66"},  {240, "67"},  {240, "68"},  {240, "69"},
    {228, "01"},  {228, "02"},  {228, "03"},  {228, "05"},
    {228, "06"},  {228, "08"},  {228, "12"},  {228, "51"},
    {746, "02"},  {746, "03"},  {746, "04"},  {746, "05"},
    {653, "01"},  {653, "10"},  {436, "01"},  {436, "02"},
    {436, "03"},  {436, "04"},  {436, "05"},  {640, "02"},
    {640, "03"},  {640, "04"},  {640, "05"},  {622, "01"},
    {622, "02"},  {520, "00"},  {520, "01"},  {520, "02"},
    {520, "03"},  {520, "04"},  {520, "05"},  {520, "15"},
    {520, "18"},  {520, "20"},  {520, "23"},  {520, "47"},
    {520, "99"},  {514, "01"},  {514, "02"},  {514, "03"},
    {615, "01"},  {539, "01"},  {539, "43"},  {539, "88"},
    {374, "12"},  {374, "130"}, {374, "140"}, {605, "02"},
    {605, "03"},  {438, "01"},  {438, "02"},  {376, "350"},
    {376, "352"}, {376, "360"}, {286, "01"},  {286, "02"},
    {286, "03"},  {286, "04"},  {553, "01"},  {255, "01"},
    {255, "02"},  {255, "03"},  {255, "04"},  {255, "05"},
    {255, "06"},  {255, "07"},  {255, "21"},  {748, "00"},
    {748, "01"},  {748, "03"},  {748, "07"},  {748, "10"},
    {541, "01"},  {541, "05"},  {541, "07"},  {734, "02"},
    {734, "04"},  {734, "06"},  {348, "170"}, {348, "370"},
    {348, "570"}, {348, "770"}, {452, "01"},  {452, "02"},
    {452, "03"},  {452, "04"},  {452, "06"},  {452, "07"},
    {452, "08"},  {421, "01"},  {421, "02"},  {421, "04"},
    {645, "01"},  {645, "02"},  {645, "03"},  {648, "01"},
    {648, "03"},  {648, "04"},  {0, "end"}  // end of list
};

int find_mnc_length(const char mcc_digit1P, const char mcc_digit2P,
                    const char mcc_digit3P, const char mnc_digit1P,
                    const char mnc_digit2P, const char mnc_digit3P) {
  int mcc =
      100 * (mcc_digit1P - 48) + 10 * (mcc_digit2P - 48) + (mcc_digit3P - 48);
  char mnc3[4];
  char mnc2[3];
  int index_l = 0;

  AssertFatal(
      (mcc_digit1P >= '0') && (mcc_digit1P <= '9') && (mcc_digit2P >= '0') &&
          (mcc_digit2P <= '9') && (mcc_digit3P >= '0') && (mcc_digit3P <= '9'),
      "BAD MCC PARAMETER (%d%d%d)!\n", mcc_digit1P, mcc_digit2P, mcc_digit3P);
  AssertFatal((mnc_digit1P >= '0') && (mnc_digit1P <= '9') &&
                  (mnc_digit2P >= '0') && (mnc_digit2P <= '9'),
              "BAD MNC PARAMETER ((%d)%d%d)!\n", mnc_digit1P, mnc_digit2P,
              mnc_digit3P);
  mnc2[0] = mnc_digit1P;
  mnc2[1] = mnc_digit2P;
  mnc2[2] = '\0';
  mnc3[0] = mnc_digit1P;
  mnc3[1] = mnc_digit2P;
  mnc3[2] = mnc_digit3P;
  mnc3[3] = '\0';

  do {
    if (mcc_mnc_list[index_l].mcc == mcc) {
      // fprintf(stdout, "Found MCC %d!\n", mcc);
      do {
        // fprintf(stdout, "Comparing MNCs %s, %s with %s\n", mnc2, mnc3,
        // mcc_mnc_list[index_l].mnc);
        if (strcmp(mnc2, mcc_mnc_list[index_l].mnc) == 0) {
          return 2;
        } else if (strcmp(mnc3, mcc_mnc_list[index_l].mnc) == 0) {
          return 3;
        }

        index_l += 1;
      } while (mcc_mnc_list[index_l].mcc == mcc);

      return 0;
    }

    index_l += 1;
  } while (mcc_mnc_list[index_l].mcc != 0);

  return 0;
}
