/* -*- C -*-
 *
 * Copyright 2011 Sandia Corporation. Under the terms of Contract
 * DE-AC04-94AL85000 with Sandia Corporation, the U.S.  Government
 * retains certain rights in this software.
 *
 * Copyright (c) 2017 Intel Corporation. All rights reserved.
 * This software is available to you under the BSD license.
 *
 * This file is part of the Sandia OpenSHMEM software package. For license
 * information, see the LICENSE file in the top level directory of the
 * distribution.
 *
 */

#include "config.h"

#define SHMEM_INTERNAL_INCLUDE
#include "shmem.h"
#include "shmem_internal.h"

#ifdef ENABLE_PROFILING
#include "pshmem.h"

#pragma weak shmem_ctx_create = pshmem_ctx_create
#define shmem_ctx_create pshmem_ctx_create

#pragma weak shmem_ctx_destroy = pshmem_ctx_destroy
#define shmem_ctx_destroy pshmem_ctx_destroy

#endif /* ENABLE_PROFILING */

SHMEM_FUNCTION_ATTRIBUTES int
shmem_ctx_create(long options, shmem_ctx_t *ctx)
{
    SHMEM_ERR_CHECK_INITIALIZED();
    SHMEM_ERR_CHECK_NULL(ctx, 1);

    return 0;
}


SHMEM_FUNCTION_ATTRIBUTES void
shmem_ctx_destroy(shmem_ctx_t ctx)
{
    SHMEM_ERR_CHECK_INITIALIZED();
    /* TODO: Error check: ctx != SHMEM_CTX_DEFAULT */

    return;
}