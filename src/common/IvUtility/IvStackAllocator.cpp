//===============================================================================
// @ IvStackAllocator.cpp
// 
// Simple heap allocator
// ------------------------------------------------------------------------------
// Copyright (C) 2014 by James M. Van Verth. All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
//===============================================================================

//-------------------------------------------------------------------------------
//-- Dependencies ---------------------------------------------------------------
//-------------------------------------------------------------------------------

#include <stdlib.h>
#include "IvStackAllocator.h"
#include "IvAssert.h"

//-------------------------------------------------------------------------------
//-- Statics --------------------------------------------------------------------
//-------------------------------------------------------------------------------

IvStackAllocator* IvStackAllocator::mScratchAllocator = NULL;

//-------------------------------------------------------------------------------
//-- Methods --------------------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
// @ IvStackAllocator::IvStackAllocator()
//-------------------------------------------------------------------------------
// Default constructor
//-------------------------------------------------------------------------------
IvStackAllocator::IvStackAllocator(size_t totalBytes)
{
    fAllocation = (unsigned char*) malloc(totalBytes);
    fTotalBytes = totalBytes;
    fCurrentOffset = 0;
}

//-------------------------------------------------------------------------------
// @ IvStackAllocator::~IvStackAllocator()
//-------------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------------
IvStackAllocator::~IvStackAllocator()
{
    free(fAllocation);
}

//-------------------------------------------------------------------------------
// @ IvStackAllocator::Allocate()
//-------------------------------------------------------------------------------
// Push an allocation onto the stack
//-------------------------------------------------------------------------------
void* IvStackAllocator::Allocate(size_t bytes)
{
    if (fCurrentOffset + bytes > fTotalBytes)
    {
        ASSERT(false);
        return NULL;
    }

    void* alloc = fAllocation + fCurrentOffset;
    fCurrentOffset += bytes;
    return alloc;
}
