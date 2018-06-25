/***********************************************************************************************************************
Author: Ziang Li
Institution: Control Group, UOM

This file defines alias names of the SRF.h.
***********************************************************************************************************************/

#pragma once
#pragma once
#ifndef __SRF_ALIAS__
#define __SRF_ALIAS__

#include "../Header_Files/ZAMATH_ALIAS.h"

typedef std::string                                  CELL;
typedef T_ROW<CELL>                                  ROW;
typedef T_TABLE<CELL>							     TABLE;


typedef T_ROW_INDEX<CELL>                            ROW_INDEX;
typedef T_ROW_SIZE<CELL>                             ROW_SIZE;
typedef T_ROWS_INDEXES_VEC<CELL>                     ROWS_INDEXES_VEC;
typedef T_ROWS_SIZES_VEC<CELL>                       ROWS_SIZES_VEC;
typedef T_CELLS_SIZES_VEC<CELL>                      CELLS_SIZES_VEC;

/*----------------------------------------------------------------------------------------------------------------------
These two should be the same for a single ROW object
----------------------------------------------------------------------------------------------------------------------*/
typedef T_ROWS_SIZES_VEC_INDEX<CELL>                 ROWS_SIZES_VEC_INDEX;
typedef T_TABLE_INDEX<CELL>                          TABLE_INDEX;
/*--------------------------------------------------------------------------------------------------------------------*/

typedef T_TABLE_SIZE<CELL>                           TABLE_SIZE;
typedef T_TABLE_INDEXES_VEC<CELL>                    TABLE_INDEXES_VEC;
typedef T_TABLE_INDEXES_VEC_INDEX<CELL>              TABLE_INDEXES_VEC_INDEX;

#endif // !__SRF_ALIAS__