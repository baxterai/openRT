/*******************************************************************************
 *
 * File Name: LDjpeg.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2010 Baxter AI (baxterai.com)
 * Project: Generic Construct Functions
 * Project Version: 3a6b 30-Apr-2012
 *
 *******************************************************************************/





#include <stdio.h>

#include "jpeglib.h"


/*
 * <setjmp.h> is used for the optional error recovery mechanism
 */
#include <setjmp.h>
#include "jmemsys.h"
#include "LDjpeg.h"

struct jvirt_barray_control {
	JBLOCKARRAY mem_buffer;	/* => the in-memory buffer */
	JDIMENSION rows_in_array;	/* total virtual array height */
	JDIMENSION blocksperrow;	/* width of array (and of memory buffer) */
	JDIMENSION maxaccess;		/* max rows accessed by access_virt_barray */
	JDIMENSION rows_in_mem;	/* height of memory buffer */
	JDIMENSION rowsperchunk;	/* allocation chunk size in mem_buffer */
	JDIMENSION cur_start_row;	/* first logical row # in the buffer */
	JDIMENSION first_undef_row;	/* row # of first uninitialized row */
	boolean pre_zero;		/* pre-zero mode requested? */
	boolean dirty;		/* do current buffer contents need written? */
	boolean b_s_open;		/* is backing-store data valid? */
	jvirt_barray_ptr next;	/* link to next virtual barray control block */
	backing_store_info b_s_info;	/* System-dependent control info */
};



struct my_error_mgr {
	struct jpeg_error_mgr pub;	/* "public" fields */

	jmp_buf setjmp_buffer;	/* for return to caller */
};

typedef struct my_error_mgr * my_error_ptr;

/*
 * Here's the routine that will replace the standard error_exit method:
 */


/*
int main()
{
	char * filename = "test3.jpg";
	readJPEGfileAndPrintDCTcoefficients (filename, NULL, NULL, NULL, DCTSIZE, DCTSIZE, false);
}
*/


METHODDEF(void) my_error_exit (j_common_ptr cinfo)
{
	/* cinfo->err really points to a my_error_mgr struct, so coerce pointer */
	my_error_ptr myerr = (my_error_ptr) cinfo->err;

	/* Always display the message. */
	/* We could postpone this until after returning, if we chose. */
	(*cinfo->err->output_message) (cinfo);

	/* Return control to the setjmp point */
	longjmp(myerr->setjmp_buffer, 1);
}

#ifdef DEBUG_OR_IMAGE_COMPARISON_DECISION_TREE_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_COMPARISON_DCT_TABLES_TO_HTML
string * pointerToDCTTableHTMLOutputString;
void setpointerToDCTTableHTMLOutputString(string * pointer)
{
	pointerToDCTTableHTMLOutputString = pointer;
}

#endif

//if storeDataInArrays, assume 1 x block and 1 y block! (image size must be <= 8x8)
int readVerySmallHighlyCompressedJPEGfileAndStoreDCTcoefficients (char * filename, signed char dctCoeffArrayY[], signed char dctCoeffArrayYCr[], signed char dctCoeffArrayYCb[], int dctCoeffArrayHeight, int dctCoeffArrayWidth, bool storeDataInArrays)
{
	jvirt_barray_ptr * coefficientarrays;
	int DCTwidth_in_blocks;
	int DCTheight_in_blocks;
	int c;
	int yBlock;
	int xBlock;
	int y=0;
	int x=0;
	int i;
	JBLOCKARRAY blockarray;
	JBLOCKROW blockrow;
	JCOEF * block;


	/* This struct contains the JPEG decompression parameters and pointers to
	* working space (which is allocated as needed by the JPEG library).
	*/
	struct jpeg_decompress_struct cinfo;
	/* We use our private extension JPEG error handler.
	* Note that this struct must live as long as the main JPEG parameter
	* struct, to avoid dangling-pointer problems.
	*/
	struct my_error_mgr jerr;
	/* More stuff */
	FILE * infile;		/* source file */
	JSAMPARRAY buffer;		/* Output row buffer */
	int row_stride;		/* physical row width in output buffer */

	/* In this example we want to open the input file before doing anything else,
	* so that the setjmp() error recovery below can assume the file is open.
	* VERY IMPORTANT: use "b" option to fopen() if you are on a machine that
	* requires it in order to read binary files.
	*/

	if ((infile = fopen(filename, "rb")) == NULL) {
	fprintf(stderr, "can't open %s\n", filename);
	return 0;
	}

	/* Step 1: allocate and initialize JPEG decompression object */

	/* We set up the normal JPEG error routines, then override error_exit. */
	cinfo.err = jpeg_std_error(&jerr.pub);
	jerr.pub.error_exit = my_error_exit;
	/* Establish the setjmp return context for my_error_exit to use. */
	if (setjmp(jerr.setjmp_buffer)) {
	/* If we get here, the JPEG code has signaled an error.
	* We need to clean up the JPEG object, close the input file, and return.
	*/
	jpeg_destroy_decompress(&cinfo);
	fclose(infile);
	return 0;
	}
	/* Now we can initialize the JPEG decompression object. */
	jpeg_create_decompress(&cinfo);

	/* Step 2: specify data source (eg, a file) */

	jpeg_stdio_src(&cinfo, infile);

	/* Step 3: read file parameters with jpeg_read_header() */

	(void) jpeg_read_header(&cinfo, TRUE);
	/* We can ignore the return value from jpeg_read_header since
	*   (a) suspension is not possible with the stdio data source, and
	*   (b) we passed TRUE to reject a tables-only JPEG file as an error.
	* See libjpeg.txt for more info.
	*/


	
	coefficientarrays = jpeg_read_coefficients(&cinfo);
	
	
  	for(c=0; c< cinfo.num_components; c++)
	{
		DCTwidth_in_blocks = cinfo.comp_info[c].width_in_blocks;
		DCTheight_in_blocks = cinfo.comp_info[c].height_in_blocks;

		blockarray = coefficientarrays[c]->mem_buffer;

		for(yBlock=0; yBlock<DCTheight_in_blocks; yBlock++)
		{
			/*
			#ifndef DEBUG_OR_IMAGE_COMPARISON_DECISION_TREE_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING
			if(!storeDataInArrays)
			{
			#endif
				printf("\n\n\nyBlock = %d", yBlock);
				#ifdef DEBUG_OR_IMAGE_COMPARISON_DECISION_TREE_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_COMPARISON_DCT_TABLES_TO_HTML
				*pointerToDCTTableHTMLOutputString = *pointerToDCTTableHTMLOutputString + "<TABLE>";
				#endif				
			#ifndef DEBUG_OR_IMAGE_COMPARISON_DECISION_TREE_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING
			}
			#endif
			*/
			
			blockrow = blockarray[yBlock]; //coefficients->mem_buffer[yblock]; //

			for(xBlock=0; xBlock<DCTwidth_in_blocks; xBlock++)
			{

				#ifndef DEBUG_OR_IMAGE_COMPARISON_DECISION_TREE_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING
				if(!storeDataInArrays)
				{
				#endif
					printf("\nxBlock = %d", xBlock);
					#ifdef DEBUG_OR_IMAGE_COMPARISON_DECISION_TREE_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_COMPARISON_DCT_TABLES_TO_HTML
					*pointerToDCTTableHTMLOutputString = *pointerToDCTTableHTMLOutputString + "<TABLE>";
					#endif						
				#ifndef DEBUG_OR_IMAGE_COMPARISON_DECISION_TREE_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING	
				}
				#endif
				block = blockrow[xBlock];

				//maybe should replace DCTSIZE here with DCT_h_scaled_size/DCT_v_scaled_size?
				for(y=0; y<dctCoeffArrayHeight; y++)
				{
					#ifndef DEBUG_OR_IMAGE_COMPARISON_DECISION_TREE_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING
					if(!storeDataInArrays)
					{
					#endif
						printf("\n");
						#ifdef DEBUG_OR_IMAGE_COMPARISON_DECISION_TREE_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_COMPARISON_DCT_TABLES_TO_HTML
						*pointerToDCTTableHTMLOutputString = *pointerToDCTTableHTMLOutputString + "<TR>";
						#endif							
					
					#ifndef DEBUG_OR_IMAGE_COMPARISON_DECISION_TREE_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING	
					}
					#endif
					for(x=0; x<dctCoeffArrayWidth; x++)
					{
						i = y*DCTSIZE + x;

						if(storeDataInArrays)
						{
							if(c == 0)
							{
								dctCoeffArrayY[y*dctCoeffArrayWidth + x] = block[i];
							}
							else if(c == 1)
							{
								dctCoeffArrayYCr[y*dctCoeffArrayWidth + x] = block[i];
							}
							else if(c == 2)
							{
								dctCoeffArrayYCb[y*dctCoeffArrayWidth + x] = block[i];
							}
						}
						
						#ifndef DEBUG_OR_IMAGE_COMPARISON_DECISION_TREE_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING
						if(!storeDataInArrays)
						{
						#endif
							//printf("DCT block coeff x=%d, y=%d, is %d", x, y, block[i]);
							printf("%d\t", block[i]);
							#ifdef DEBUG_OR_IMAGE_COMPARISON_DECISION_TREE_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_COMPARISON_DCT_TABLES_TO_HTML
							char dataValueString[100];
							sprintf(dataValueString, "%d", block[i]);
							*pointerToDCTTableHTMLOutputString = *pointerToDCTTableHTMLOutputString + "<TD>" + dataValueString + "</TD>";
							#endif							
						#ifndef DEBUG_OR_IMAGE_COMPARISON_DECISION_TREE_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING
						}
						#endif

					}
					#ifndef DEBUG_OR_IMAGE_COMPARISON_DECISION_TREE_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING
					if(!storeDataInArrays)
					{
					#endif
						#ifdef DEBUG_OR_IMAGE_COMPARISON_DECISION_TREE_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_COMPARISON_DCT_TABLES_TO_HTML
						*pointerToDCTTableHTMLOutputString = *pointerToDCTTableHTMLOutputString + "</TR>";
						#endif							
					
					#ifndef DEBUG_OR_IMAGE_COMPARISON_DECISION_TREE_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING	
					}
					#endif					
				}
				#ifndef DEBUG_OR_IMAGE_COMPARISON_DECISION_TREE_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING
				if(!storeDataInArrays)
				{
				#endif
					#ifdef DEBUG_OR_IMAGE_COMPARISON_DECISION_TREE_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_COMPARISON_DCT_TABLES_TO_HTML
					*pointerToDCTTableHTMLOutputString = *pointerToDCTTableHTMLOutputString + "</TABLE>";
					#endif				
				#ifndef DEBUG_OR_IMAGE_COMPARISON_DECISION_TREE_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING
				}
				#endif					

			}
			
			/*
			#ifndef DEBUG_OR_IMAGE_COMPARISON_DECISION_TREE_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING
			if(!storeDataInArrays)
			{
			#endif
				#ifdef DEBUG_OR_IMAGE_COMPARISON_DECISION_TREE_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING_COMPARISON_DCT_TABLES_TO_HTML
				*pointerToDCTTableHTMLOutputString = *pointerToDCTTableHTMLOutputString + "</TABLE>";
				#endif				
			#ifndef DEBUG_OR_IMAGE_COMPARISON_DECISION_TREE_PATTERN_RECOGNITION_FOURIER_TRANSFORM_BINNING
			}
			#endif	
			*/		
		}
	}

	if(!storeDataInArrays)
	{
		printf("\n number of components (y Cb Cr / R G B) = %d", c);
		printf("\n number yBlocks = %d", yBlock);
		printf("\n number xBlocks = %d", xBlock);
		/*
		printf("\n cinfo.comp_info[c].downsampled_height = %d", cinfo.comp_info[c].downsampled_height);
		printf("\n cinfo.comp_info[c].downsampled_width = %d", cinfo.comp_info[c].downsampled_width);
		printf("\n cinfo.comp_info[c].DCT_h_scaled_size = %d", cinfo.comp_info[c].DCT_h_scaled_size);
		printf("\n cinfo.comp_info[c].DCT_v_scaled_size = %d", cinfo.comp_info[c].DCT_v_scaled_size);
		*/
	}
	

	/* This is an important step since it will release a good deal of memory. */
	jpeg_destroy_decompress(&cinfo);

	/* After finish_decompress, we can close the input file.
	* Here we postpone it until after no more JPEG errors are possible,
	* so as to simplify the setjmp error logic above.  (Actually, I don't
	* think that jpeg_destroy can do an error exit, but why assume anything...)
	*/
	fclose(infile);

	/* At this point you may want to check to see whether any corrupt-data
	* warnings occurred (test whether jerr.pub.num_warnings is nonzero).
	*/

	/* And we're done! */
	return true;
}



