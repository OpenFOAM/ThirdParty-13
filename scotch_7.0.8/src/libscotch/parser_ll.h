/* Copyright 2004,2007,2018,2021,2025 IPB, Universite de Bordeaux, INRIA & CNRS
**
** This file is part of the Scotch software package for static mapping,
** graph partitioning and sparse matrix ordering.
**
** This software is governed by the CeCILL-C license under French law
** and abiding by the rules of distribution of free software. You can
** use, modify and/or redistribute the software under the terms of the
** CeCILL-C license as circulated by CEA, CNRS and INRIA at the following
** URL: "http://www.cecill.info".
**
** As a counterpart to the access to the source code and rights to copy,
** modify and redistribute granted by the license, users are provided
** only with a limited warranty and the software's author, the holder of
** the economic rights, and the successive licensors have only limited
** liability.
**
** In this respect, the user's attention is drawn to the risks associated
** with loading, using, modifying and/or developing or reproducing the
** software by the user in light of its specific status of free software,
** that may mean that it is complicated to manipulate, and that also
** therefore means that it is reserved for developers and experienced
** professionals having in-depth computer knowledge. Users are therefore
** encouraged to load and test the software's suitability as regards
** their requirements in conditions enabling the security of their
** systems and/or data to be ensured and, more generally, to use and
** operate it in the same conditions as regards security.
**
** The fact that you are presently reading this means that you have had
** knowledge of the CeCILL-C license and that you accept its terms.
*/
/************************************************************/
/**                                                        **/
/**   NAME       : parser_ll.h                             **/
/**                                                        **/
/**   AUTHOR     : Francois PELLEGRINI                     **/
/**                                                        **/
/**   FUNCTION   : Part of a static mapper.                **/
/**                These lines are the declarations for    **/
/**                the strategy strings lexical parser.    **/
/**                                                        **/
/**   DATES      : # Version 3.1  : from : 07 nov 1995     **/
/**                                 to   : 13 jun 1996     **/
/**                # Version 3.2  : from : 03 oct 1996     **/
/**                                 to   : 19 oct 1996     **/
/**                # Version 3.3  : from : 01 oct 1998     **/
/**                                 to   : 01 oct 1998     **/
/**                # Version 4.0  : from : 20 dec 2001     **/
/**                                 to   : 20 dec 2001     **/
/**                # Version 6.0  : from : 07 jun 2018     **/
/**                                 to   : 07 jun 2018     **/
/**                # Version 7.0  : from : 02 mar 2018     **/
/**                                 to   : 08 jun 2025     **/
/**                                                        **/
/************************************************************/

/*
**  The function prototypes.
*/

void                        stratParserLexBufDelete (YY_BUFFER_STATE, yyscan_t);
void                        stratParserLexBufSwitch (YY_BUFFER_STATE, yyscan_t);
void                        stratParserLexBegin (yyscan_t, unsigned int);
int                         stratParserLexDestroy (yyscan_t);
int                         stratParserLexInit  (yyscan_t *);
YY_BUFFER_STATE             stratParserLexScanString (const char *, yyscan_t);
