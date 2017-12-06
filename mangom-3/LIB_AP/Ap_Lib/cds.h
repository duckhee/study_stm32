#ifndef __CDS_H__
#define __CDS_H__

#include "Ap.h"

#ifdef CDS_LOCAL
#define CDS_DEF
#else
#define CDS_DEF              extern
#endif

#define CDS_MAX_LIMIT       100

CDS_DEF void Cds_Init(void);
CDS_DEF uint16_t Cds_GetData(void);

#endif