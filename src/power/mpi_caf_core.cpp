/* Core caf functions
*
* Copyright (c) 2012-2019, Sourcery, Inc.
* Copyright (c) 2012-2019, Sourcery Institute
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*     * Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
*     * Neither the name of the Sourcery, Inc., nor the
*       names of its contributors may be used to endorse or promote products
*       derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL SOURCERY, INC., BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
* THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */

#include <cassert>
#include <iostream>

#include "libcaf.h"

// Global variables
static int caf_this_img;
static int caf_num_imgs = 0;
static bool caf_is_finalized = false;

// Create images -- assuming no other MPI initialization happened before.
// TODO:: Assert that no other MPI initialization has happened before
void caf_init (int *argc, char ***argv)
{
   int ierr = MPI_Init(argc, argv);

   assert(ierr == MPI_SUCCESS);
}

// Execute normal termination of an image.
void caf_finalize()
{
   int ierr = MPI_Finalize();

   if (ierr == MPI_SUCCESS) {
      caf_is_finalized = true;
   }
}

// ERROR STOP function for numerical arguments.
void caf_error_stop(int error, bool quiet)
{
   if (!quiet)
      std::cerr << "ERROR STOP " << error << "\n";

   MPI_Abort(MPI_COMM_WORLD, error);

   //   exit(error);

}

// Return number of images
int caf_num_images(int team_number)
{
   int images;
   MPI_Comm_size(MPI_COMM_WORLD, &images);

   return images;
}

// return id of this image
int caf_this_image()
{
   int image;
   MPI_Comm_rank(MPI_COMM_WORLD, &image);

   // incrementing image to represent Fortran indexing
   return ++image;
}

void caf_sync_all()
{
   MPI_Barrier(MPI_COMM_WORLD);
}