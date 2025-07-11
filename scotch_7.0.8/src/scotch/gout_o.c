/* Copyright 2004,2007,2008,2011,2012,2018,2021,2023,2025 IPB, Universite de Bordeaux, INRIA & CNRS
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
/**   NAME       : gout_o.c                                **/
/**                                                        **/
/**   AUTHOR     : Francois PELLEGRINI                     **/
/**                                                        **/
/**   FUNCTION   : Part of a result viewer.                **/
/**                This module contains output routines.   **/
/**                                                        **/
/**   DATES      : # Version 2.0  : from : 07 oct 1994     **/
/**                                 to   : 23 dec 1994     **/
/**                # Version 3.0  : from : 14 jul 1995     **/
/**                                 to   : 03 oct 1995     **/
/**                # Version 3.1  : from : 28 mar 1996     **/
/**                                 to   : 03 jun 1996     **/
/**                # Version 3.2  : from : 02 dec 1996     **/
/**                                 to   : 05 jun 1998     **/
/**                # Version 3.3  : from : 29 may 1999     **/
/**                                 to   : 03 jun 1999     **/
/**                # Version 4.0  : from : 11 dec 2001     **/
/**                                 to   : 11 dec 2001     **/
/**                # Version 5.0  : from : 25 may 2007     **/
/**                                 to   : 18 jun 2007     **/
/**                # Version 5.1  : from : 25 oct 2007     **/
/**                                 to   : 14 feb 2011     **/
/**                # Version 6.0  : from : 01 jan 2012     **/
/**                                 to   : 21 may 2018     **/
/**                # Version 6.1  : from : 04 apr 2021     **/
/**                                 to   : 28 aug 2021     **/
/**                # Version 7.0  : from : 31 aug 2021     **/
/**                                 to   : 09 jul 2025     **/
/**                                                        **/
/************************************************************/

/*
**  The defines and includes
*/

#include "module.h"
#include "common.h"
#include "scotch.h"
#include "gout_c.h"
#include "gout_o.h"

/*
**  The static and global variables
*/

static O_OutParam           O_outParam = {        /* Parameter structure        */
                              O_OUTTYPEVTKMESH,   /* Default output type        */
                              { 'c', 'v' },       /* OpenInventor mesh defaults */
                              { 'f' },            /* PostScript matrix defaults */
                              { 'f', 'g',         /* PostScript mesh defaults   */
                                'v', 'd',
                                's',
                                { { 0.0, 0.0 } },
                                { { 1.0, 1.0 } } },
                              { 'c', 'v', 'a' },  /* Tulip graph defaults       */
                              { 'v' } };          /* VTK mesh defaults          */

static C_ParseCode          O_outList[] = {       /* Output code list */
                              { O_OUTTYPEINVMESH, "i"  },
                              { O_OUTTYPEPOSMATR, "m"  },
                              { O_OUTTYPEPOSMESH, "p"  },
                              { O_OUTTYPETULMESH, "t"  },
                              { O_OUTTYPEVTKMESH, "v"  },
                              { O_OUTTYPENBR,     NULL } };

static C_ParseArg           O_outArg[] = {        /* Output type argument list */
                              { "c",  O_OUTTYPEINVMESH, NULL,  &O_outParam.InvMesh.color },
                              { "g",  O_OUTTYPEINVMESH, NULL,  &O_outParam.InvMesh.color },
                              { "r",  O_OUTTYPEINVMESH, NULL,  &O_outParam.InvMesh.edge  },
                              { "v",  O_OUTTYPEINVMESH, NULL,  &O_outParam.InvMesh.edge  },
                              { "e",  O_OUTTYPEPOSMATR, NULL,  &O_outParam.PosMatr.type  },
                              { "f",  O_OUTTYPEPOSMATR, NULL,  &O_outParam.PosMatr.type  },
                              { "c",  O_OUTTYPEPOSMESH, NULL,  &O_outParam.PosMesh.color },
                              { "g",  O_OUTTYPEPOSMESH, NULL,  &O_outParam.PosMesh.color },
                              { "e",  O_OUTTYPEPOSMESH, NULL,  &O_outParam.PosMesh.type  },
                              { "f",  O_OUTTYPEPOSMESH, NULL,  &O_outParam.PosMesh.type  },
                              { "l",  O_OUTTYPEPOSMESH, NULL,  &O_outParam.PosMesh.clip  },
                              { "s",  O_OUTTYPEPOSMESH, NULL,  &O_outParam.PosMesh.clip  },
                              { "a",  O_OUTTYPEPOSMESH, NULL,  &O_outParam.PosMesh.disk  },
                              { "d",  O_OUTTYPEPOSMESH, NULL,  &O_outParam.PosMesh.disk  },
                              { "r",  O_OUTTYPEPOSMESH, NULL,  &O_outParam.PosMesh.edge  },
                              { "v",  O_OUTTYPEPOSMESH, NULL,  &O_outParam.PosMesh.edge  },
                              { "x",  O_OUTTYPEPOSMESH, "%lf", &O_outParam.PosMesh.min.x },
                              { "X",  O_OUTTYPEPOSMESH, "%lf", &O_outParam.PosMesh.max.x },
                              { "y",  O_OUTTYPEPOSMESH, "%lf", &O_outParam.PosMesh.min.y },
                              { "Y",  O_OUTTYPEPOSMESH, "%lf", &O_outParam.PosMesh.max.y },
                              { "b",  O_OUTTYPETULMESH, NULL,  &O_outParam.TulMesh.color },
                              { "c",  O_OUTTYPETULMESH, NULL,  &O_outParam.TulMesh.color },
                              { "r",  O_OUTTYPETULMESH, NULL,  &O_outParam.TulMesh.edge  },
                              { "v",  O_OUTTYPETULMESH, NULL,  &O_outParam.TulMesh.edge  },
                              { "a",  O_OUTTYPETULMESH, NULL,  &O_outParam.TulMesh.disk  },
                              { "d",  O_OUTTYPETULMESH, NULL,  &O_outParam.TulMesh.disk  },
                              { "r",  O_OUTTYPEVTKMESH, NULL,  &O_outParam.VtkMesh.edge  },
                              { "v",  O_OUTTYPEVTKMESH, NULL,  &O_outParam.VtkMesh.edge  },
                              { NULL, O_OUTTYPENBR,     "",    NULL                      } };

static double               outcolorcoltab[16][3] = { /* Color list */
                              { 1.00, 0.00, 0.00 }, /* Red          */
                              { 0.00, 1.00, 0.00 }, /* Green        */
                              { 1.00, 1.00, 0.00 }, /* Yellow       */
                              { 0.00, 0.00, 1.00 }, /* Blue         */
                              { 1.00, 0.00, 1.00 }, /* Magenta      */
                              { 0.00, 1.00, 1.00 }, /* Cyan         */
                              { 1.00, 0.50, 0.20 }, /* Orange       */
                              { 0.30, 0.55, 0.00 }, /* Olive        */
                              { 0.72, 0.47, 0.47 }, /* Dark pink    */
                              { 0.33, 0.33, 0.81 }, /* Sea blue     */
                              { 1.00, 0.63, 0.63 }, /* Pink         */
                              { 0.62, 0.44, 0.65 }, /* Violet       */
                              { 0.60, 0.80, 0.70 }, /* Pale green   */
                              { 0.47, 0.20, 0.00 }, /* Brown        */
                              { 0.00, 0.68, 0.68 }, /* Turquoise    */
                              { 0.81, 0.00, 0.40 } }; /* Purple     */

static double               outcolorblwtab[8][3] = { /* Grey list */
                              { 1.00, 1.00, 1.00 },
                              { 0.20, 0.20, 0.20 },
                              { 0.50, 0.50, 0.50 },
                              { 0.80, 0.80, 0.80 },
                              { 0.30, 0.30, 0.30 },
                              { 0.90, 0.90, 0.90 },
                              { 0.40, 0.40, 0.40 },
                              { 0.70, 0.70, 0.70 } };

/****************************************/
/*                                      */
/* This is the color selection routine. */
/*                                      */
/****************************************/

void
outColorBlw (
const SCOTCH_Num            labl,
double                      color[])
{
  if (labl == (-1)) {
    color[0] =
    color[1] =
    color[2] = 1.0L;
  }
  else {
    color[0] = (double) outcolorblwtab[labl % 8][0];
    color[1] = (double) outcolorblwtab[labl % 8][1];
    color[2] = (double) outcolorblwtab[labl % 8][2];
  }
}

void
outColorColor (
const SCOTCH_Num            labl,
double                      color[])
{
  if (labl == (-1)) {
    color[0] =
    color[1] =
    color[2] = 1.0L;
  }
  else {
    color[0] = (double) outcolorcoltab[labl % 16][0];
    color[1] = (double) outcolorcoltab[labl % 16][1];
    color[2] = (double) outcolorcoltab[labl % 16][2];
  }
}

/****************************/
/*                          */
/* The main output routine. */
/*                          */
/****************************/

/* This routine parses the output
** option string.
** It returns:
** - 0  : if string successfully scanned.
** - 1  : if invalid options
** - 2  : if invalid option arguments.
** - 3  : if syntax error in string.
*/

int
outDrawParse (
char * const                string)
{
  return (C_parse (O_outList, O_outArg, (int * const) (void *) &O_outParam.type, string));
}


/* This routine is the generic output call.
** It returns:
** - VOID  : in all cases.
*/

void
outDraw (
const C_Graph * const       grafptr,              /* Graph structure */
const C_Geometry * const    geomptr,              /* Graph geometry  */
const C_Mapping * const     mapptr,               /* Result mapping  */
FILE * const                stream)               /* Output stream   */
{
  switch (O_outParam.type) {
    case O_OUTTYPEINVMESH :                       /* Mesh OpenInventor output type */
      outDrawInvMesh (grafptr, geomptr, mapptr, stream);
      break;
    case O_OUTTYPEPOSMATR :                       /* Matrix PostScript output type */
      outDrawPosMatr (grafptr, geomptr, mapptr, stream);
      break;
    case O_OUTTYPEPOSMESH :                       /* Mesh PostScript output type */
      outDrawPosMesh (grafptr, geomptr, mapptr, stream);
      break;
    case O_OUTTYPETULMESH :                       /* Mesh Tulip output type */
      outDrawTulMesh (grafptr, geomptr, mapptr, stream);
      break;
    case O_OUTTYPEVTKMESH :                       /* Mesh Tulip output type */
      outDrawVtkMesh (grafptr, geomptr, mapptr, stream);
      break;
    default :
      errorPrint ("outDraw: invalid output method '%d'", O_outParam.type);
  }
}

/****************************************/
/*                                      */
/* This is the Inventor output routine. */
/*                                      */
/****************************************/

int
outDrawInvMesh (
const C_Graph * const       grafptr,              /* Graph structure, sorted by vertex index */
const C_Geometry * const    geomptr,              /* Graph geometry, sorted by vertex label  */
const C_Mapping * const     mapptr,               /* Result mapping, sorted by vertex label  */
FILE * const                stream)               /* Output stream                           */
{
  void             (* outcolor) (const SCOTCH_Num, double[]); /* Color routine   */
  O_InvMeshPath *     pattab;                     /* Array of path building data */
  SCOTCH_Num *        idxtab;                     /* Array of indexes            */
  SCOTCH_Num          idxnbr;                     /* Number of indexes           */
  time_t              pictime;                    /* Creation time               */
  double              color[3];                   /* Vertex color                */
  SCOTCH_Num          i, j, k;

  if (geomptr->verttab == NULL) {
    errorPrint ("outDrawInvMesh: geometry not provided");
    return (1);
  }

  time (&pictime);                                /* Get current time */

  outcolor = (O_outParam.InvMesh.color == 'c') ? outColorColor : outColorBlw; /* Select color output routine */

  if (memAllocGroup ((void **) (void *)
                     &idxtab, (size_t) ((grafptr->edgenbr / 2) * 3 * sizeof (SCOTCH_Num)),
                     &pattab, (size_t) (grafptr->vertnbr           * sizeof (O_InvMeshPath)), NULL) == NULL) {
    errorPrint ("outDrawInvMesh: out of memory");
    return (1);
  }
  idxnbr = 0;                                     /* No indexes yet */

  for (i = 0, j = 0; i < grafptr->vertnbr; i ++) { /* For all vertices                  */
    pattab[i].nbr = 0;                            /* Compute the number of output paths */
    pattab[i].idx = grafptr->verttab[i];
    for ( ; j < grafptr->vendtab[i]; j ++) {
      if ((grafptr->edgetab[j] > i) &&            /* If it can be an output edge */
          ((O_outParam.InvMesh.edge != 'r') ||    /* And this edge can be drawn  */
           (mapptr->labltab[i] == mapptr->labltab[grafptr->edgetab[j]])))
        pattab[i].nbr ++;                         /* One more path to higher vertices */
    }
  }
  for (i = 0; i < grafptr->vertnbr; ) {           /* For all vertices                  */
    if (pattab[i].nbr == 0) {                     /* If no output path for this vertex */
      i ++;                                       /* Skip to next vertex               */
      continue;
    }

    j = i;                                        /* Begin with this vertex        */
    idxtab[idxnbr ++] = j;                        /* Add it to the current segment */
    do {
      for (k = pattab[j].idx; k < grafptr->vendtab[j]; k ++) { /* Search for first output */
        if ((grafptr->edgetab[k] > j) &&          /* If it can be an output edge          */
          ((O_outParam.InvMesh.edge != 'r') ||    /* And this edge can be drawn           */
           (mapptr->labltab[j] == mapptr->labltab[grafptr->edgetab[k]])))
          break;
      }
      pattab[j].nbr --;                           /* One less output path remaining */
      pattab[j].idx = k + 1;                      /* Search from the next position  */
      j = grafptr->edgetab[k];                    /* Get the path end vertex number */
      idxtab[idxnbr ++] = j;                      /* Add it to the current segment  */
    } while (pattab[j].nbr > 0);                  /* As long as there is a path     */
    idxtab[idxnbr ++] = ~0;                       /* Mark end of path               */
  }

  fprintf (stream, "#Inventor V2.0 ascii\n");     /* Write header */
  fprintf (stream, "#Title: %s %s %s\n",
           C_filenamesrcinp, C_filenamegeoinp, C_filenamemapinp);
  fprintf (stream, "#Creator: Scotch/gout\n");
  fprintf (stream, "#CreationDate: %s", ctime (&pictime));

  if (idxnbr == 0)                                /* If nothing to write */
    return (0);

  fprintf (stream, "Separator {\n");
  fprintf (stream, "  LightModel {\n    model\t\tBASE_COLOR\n  }\n");
  fprintf (stream, "  DrawStyle {\n    style\t\tLINES\n  }\n");
  fprintf (stream, "  MaterialBinding {\n    value\t\tPER_VERTEX\n  }\n");

  fprintf (stream, "  Coordinate3 {\n    point [\n\t%g\t%g\t%g", /* Write vertex coordinates */
           geomptr->verttab[0].x,
           geomptr->verttab[0].y,
           geomptr->verttab[0].z);
  for (i = 1; i < grafptr->vertnbr; i ++)
    fprintf (stream, ",\n\t%g\t%g\t%g",
             geomptr->verttab[i].x,
             geomptr->verttab[i].y,
             geomptr->verttab[i].z);
  fprintf (stream, " ]\n  }\n");

  fprintf (stream, "  BaseColor {\n    rgb [");   /* Write color vector */
  for (i = 0; i < idxnbr - 2; i ++) {
    if (idxtab[i] != ~0) {
      outcolor (mapptr->labltab[idxtab[i]], color);
      fprintf (stream, "\n\t%g\t%g\t%g,",
               (double) color[0],
               (double) color[1],
               (double) color[2]);
    }
  }
  outcolor (mapptr->labltab[idxtab[idxnbr - 2]], color);
  fprintf (stream, "\n\t%g\t%g\t%g ]\n  }\n",
           (double) color[0],
           (double) color[1],
           (double) color[2]);

  fprintf (stream, "  IndexedLineSet {\n    coordIndex ["); /* Write set of lines */
  for (i = 0; i < idxnbr - 1; i ++) {
    if ((i % 8) == 0)
      fprintf (stream, "\n");
    fprintf (stream, "\t" SCOTCH_NUMSTRING ",", idxtab[i]); /* ~0 is "1" */
  }
  if (((idxnbr - 1) % 8) == 0)
    fprintf (stream, "\n");
  fprintf (stream, "\t-1 ]\n  }\n");

  fprintf (stream, "}\n");                        /* Write end of separator */


#if 0
  for (i = 0; i < grafptr->vertnbr; i ++) {       /* For all vertices */
    outcolor (mapptr->labltab[i], color);
    fprintf (stream, "Separator { Translation { translation %lg %lg %lg } BaseColor { rgb [ %lg %lg %lg ] } Sphere { radius 0.3 } }\n",
             geomptr->verttab[i].x,
             geomptr->verttab[i].y,
             geomptr->verttab[i].z,
             (double) color[0],
             (double) color[1],
             (double) color[2]);
  }
#endif

  memFree (idxtab);                               /* Free group leader */

  return (0);
}

/*************************************************/
/*                                               */
/* This is the PostScript matrix output routine. */
/*                                               */
/*************************************************/

int
outDrawPosMatr (
const C_Graph * const       grafptr,              /* Graph structure, sorted by vertex index */
const C_Geometry * const    geomptr,              /* Graph geometry, sorted by vertex label  */
const C_Mapping * const     mapptr,               /* Result mapping, sorted by vertex label  */
FILE * const                stream)               /* Output stream                           */
{
  SCOTCH_Num *        nonztab;                    /* Array of non-zero entries              */
  SCOTCH_Num          nonzfrst;                   /* First non-zero entry of area           */
  SCOTCH_Num          nonzlast;                   /* Last non-zero entry of area            */
  double              pictsize;                   /* Number of distinct coordinates         */
  double              pictdisp;                   /* Size of the matrix display (in inches) */
  time_t              picttime;                   /* Creation time                          */
  SCOTCH_Num          colnum;
  SCOTCH_Num          vertnum;
  SCOTCH_Num *        edgeptr;

  if ((nonztab = memAlloc ((grafptr->vertnbr + 1) * sizeof (SCOTCH_Num))) == NULL) {
    errorPrint ("outDrawPosMatr: out of memory");
    return (1);
  }

  time (&picttime);                               /* Get current time */
  pictsize = (double) (grafptr->vertnbr + 1);     /* Get matrix size  */
  pictdisp = MIN (O_PSPICTWIDTH, O_PSPICTHEIGHT);

  if (O_outParam.PosMatr.type == 'e') {           /* EPSF-type output */
    fprintf (stream, "%%!PS-Adobe-2.0 EPSF-2.0\n");
    fprintf (stream, "%%%%Title: %s %s %s\n",
             C_filenamesrcinp, C_filenamegeoinp, C_filenamemapinp);
    fprintf (stream, "%%%%Creator: Scotch/gout\n");
    fprintf (stream, "%%%%CreationDate: %s", ctime (&picttime));
    fprintf (stream, "%%%%BoundingBox: 0 0 %d %d\n",
             (int) (pictdisp * O_PSDPI), (int) (pictdisp * O_PSDPI));
    fprintf (stream, "%%%%Pages: 0\n");
    fprintf (stream, "%%%%EndComments\n");
  }
  else {                                          /* Full page output */
    fprintf (stream, "%%!PS-Adobe-2.0\n");
    fprintf (stream, "%%%%Title: %s %s %s\n",
             C_filenamesrcinp, C_filenamegeoinp, C_filenamemapinp);
    fprintf (stream, "%%%%Creator: Scotch/gout\n");
    fprintf (stream, "%%%%CreationDate: %s", ctime (&picttime));
  }

  fprintf (stream, "/p { pop } bind def\n");
  fprintf (stream, "/h { 3 1 roll exch 2 copy moveto 2 copy 1 add 5 -3 roll 3 1 roll add exch 2 copy lineto 1 add lineto lineto fill } bind def\n");
  fprintf (stream, "/v { 3 copy pop moveto 2 copy add exch pop exch 3 copy pop pop 1 add dup 3 -1 roll lineto exch dup 3 1 roll lineto lineto fill } bind def\n");
  fprintf (stream, "/b { 3 copy v 3 copy h pop pop } bind def\n");
  fprintf (stream, "/c { 1 3 copy v 3 copy h pop pop } bind def\n");

  fprintf (stream, "gsave\n");                    /* Save the context    */
  fprintf (stream, "0 setlinecap\n");             /* Perform miter caps  */
  if (O_outParam.PosMatr.type == 'f')             /* If full page output */
    fprintf (stream, "%d %d translate\n",         /* Center the picture  */
             (int) (O_PSDPI * (O_PSPAGEWIDTH - pictdisp)) / 2,
             (int) (O_PSDPI * (O_PSPAGEWIDTH - pictdisp)) / 2);
  fprintf (stream, "%f %f scale\n",               /* Print scaling factor */
           (double) O_PSDPI * pictdisp / pictsize,
           (double) O_PSDPI * pictdisp / pictsize);
  fprintf (stream, "[ 1 0 0 -1 0 %d ] concat\n",  /* Reverse Y coordinate */
           (int) (grafptr->vertnbr + 1));
  fprintf (stream, "0 setgray newpath\n");        /* Select black color */

  for (vertnum = 0; vertnum < grafptr->vertnbr; vertnum ++) {
    colnum = (mapptr->labltab[vertnum] == ~0) ? vertnum : mapptr->labltab[vertnum];

    fprintf (stream, SCOTCH_NUMSTRING "\n",       /* Set column value */
             (SCOTCH_Num) colnum);
    memset (nonztab, 0, (colnum + 2) * sizeof (SCOTCH_Num));
    for (edgeptr = grafptr->edgetab + grafptr->verttab[colnum];
         edgeptr < grafptr->edgetab + grafptr->vendtab[colnum]; edgeptr ++) {
      if (*edgeptr < colnum)
        nonztab[*edgeptr] = 1;
    }
    nonztab[colnum] = 1;                          /* Diagonal is non-zero */
    for (nonzfrst = 0; nonzfrst <= vertnum; nonzfrst ++) {
      if (nonztab[nonzfrst] != 0) {               /* A non-zero has been found */
        for (nonzlast = nonzfrst; nonztab[nonzlast] != 0; nonzlast ++) ;
        if ((nonzlast - nonzfrst) > 1)            /* Draw row block coefficient */
          fprintf (stream, SCOTCH_NUMSTRING " " SCOTCH_NUMSTRING " b\n",
                   (SCOTCH_Num) nonzfrst,
                   (SCOTCH_Num) (nonzlast - nonzfrst));
        else
          fprintf (stream, SCOTCH_NUMSTRING " c\n",
                   (SCOTCH_Num) nonzfrst);
        nonzfrst = nonzlast - 1;
      }
    }
    fprintf (stream, "p ");                       /* Close the column */
  }

  fprintf (stream, "\ngrestore\n");               /* Restore context     */
  if (O_outParam.PosMatr.type == 'f')             /* If full page output */
    fprintf (stream, "showpage\n");               /* Display the page    */

  memFree (nonztab);

  return (0);
}

/***********************************************/
/*                                             */
/* This is the PostScript mesh output routine. */
/*                                             */
/***********************************************/

int
outDrawPosMesh (
const C_Graph * const       grafptr,              /* Graph structure, sorted by vertex index */
const C_Geometry * const    geomptr,              /* Graph geometry, sorted by vertex label  */
const C_Mapping * const     mapptr,               /* Result mapping, sorted by vertex label  */
FILE * const                stream)               /* Output stream                           */
{
  SCOTCH_Num          idxnbr;                     /* Number of indexes                               */
  SCOTCH_Num *        idxtab;                     /* Array of indexes                                */
  O_PosMeshPath *     pattab;                     /* Array of path building data                     */
  O_PosMeshVertex *   pictab;                     /* Array of 2D coordinates, sorted by vertex index */
  O_Point             picmin;                     /* Picture minimum and maximum coordinates         */
  O_Point             picmax;
  O_Point             picdelt;
  double              picscale;                   /* Scaling factor          */
  double              picsrad;                    /* Square of circle radius */
  time_t              pictime;                    /* Creation time           */
  double              color[3];                   /* Color values            */
  SCOTCH_Num          i, j, k;

  if (geomptr->verttab == NULL) {
    errorPrint ("outDrawPosMesh: geometry not provided");
    return (1);
  }

  time (&pictime);                                /* Get current time */

  if (((pictab = (O_PosMeshVertex *) memAlloc (grafptr->vertnbr *           sizeof (O_PosMeshVertex))) == NULL) ||
      ((idxtab = (SCOTCH_Num *)      memAlloc ((grafptr->edgenbr / 2) * 3 * sizeof (SCOTCH_Num)))      == NULL) ||
      ((pattab = (O_PosMeshPath *)   memAlloc (grafptr->vertnbr *           sizeof (O_PosMeshPath)))   == NULL)) {
    errorPrint ("outDrawPosMesh: out of memory");
    if (pictab != NULL) {
      if (idxtab != NULL)
        memFree (idxtab);
      memFree (pictab);
    }
    return (1);
  }

  for (i = 0; i < grafptr->vertnbr; i ++) {       /* For all vertex indices              */
    pictab[i].pos.x = geomptr->verttab[i].x +     /* Project 3D coordinates into 2D ones */
                      geomptr->verttab[i].z * (O_POSMESHISOCOS * O_POSMESHISOREDUC);
    pictab[i].pos.y = geomptr->verttab[i].y +
                      geomptr->verttab[i].z * (O_POSMESHISOSIN * O_POSMESHISOREDUC);
  }

  picmin.x = picmin.y =  1e30;                    /* Pre-set coordinates extrema */
  picmax.x = picmax.y = -1e30;

  if (O_outParam.PosMesh.clip == 'l') {           /* If clipping encompasses disks  */
    for (i = 0, j = 0; i < grafptr->vertnbr; i ++) {
      pictab[i].rad = 1e30;                       /* Assume a huge square of radius */
      for ( ; j < grafptr->vendtab[i]; j ++) {
        k = grafptr->edgetab[j];
        picsrad = (pictab[i].pos.x - pictab[k].pos.x) *
                  (pictab[i].pos.x - pictab[k].pos.x) +
                  (pictab[i].pos.y - pictab[k].pos.y) *
                  (pictab[i].pos.y - pictab[k].pos.y);
        if (picsrad < pictab[i].rad)              /* Get the smallest square of radius */
         pictab[i].rad = picsrad;
      }
      pictab[i].rad = sqrt (pictab[i].rad) / 2.0; /* Keep the half-distance for radius */

      if ((pictab[i].pos.x - pictab[i].rad) < picmin.x) /* Update extrema if necessary */
        picmin.x = pictab[i].pos.x - pictab[i].rad;
      if ((pictab[i].pos.y - pictab[i].rad) < picmin.y)
        picmin.y = pictab[i].pos.y - pictab[i].rad;
      if ((pictab[i].pos.x + pictab[i].rad) > picmax.x)
        picmax.x = pictab[i].pos.x + pictab[i].rad;
      if ((pictab[i].pos.y + pictab[i].rad) > picmax.y)
        picmax.y = pictab[i].pos.y + pictab[i].rad;
    }
  }
  else {                                          /* Border clipping             */
    for (i = 0; i < grafptr->vertnbr; i ++) {     /* For all vertex indices      */
      if (pictab[i].pos.x < picmin.x)             /* Update extrema if necessary */
        picmin.x = pictab[i].pos.x;
      if (pictab[i].pos.y < picmin.y)
        picmin.y = pictab[i].pos.y;
      if (pictab[i].pos.x > picmax.x)
        picmax.x = pictab[i].pos.x;
      if (pictab[i].pos.y > picmax.y)
        picmax.y = pictab[i].pos.y;
    }
  }

  picdelt.x = picmax.x - picmin.x;                /* Compute picture extents */
  picdelt.y = picmax.y - picmin.y;
  picmin.x += picdelt.x * O_outParam.PosMesh.min.x; /* Resize picture (if necessary) */
  picmin.y += picdelt.y * O_outParam.PosMesh.min.y;
  picmax.x -= picdelt.x * (1.0L - O_outParam.PosMesh.max.x);
  picmax.y -= picdelt.y * (1.0L - O_outParam.PosMesh.max.y);
  picdelt.x = picmax.x - picmin.x;                /* Recompute picture extents */
  picdelt.y = picmax.y - picmin.y;

  picscale = (picdelt.x == 0.0L)                  /* Compute scaling factor */
             ? ((picdelt.y == 0.0L)
                ? 1.0L
                : (O_PSPICTHEIGHT / picdelt.y))
             : ((picdelt.y == 0.0L)
                ? (O_PSPICTWIDTH / picdelt.x)
                : MIN (O_PSPICTWIDTH  / picdelt.x, O_PSPICTHEIGHT / picdelt.y));

  picdelt.x *= picscale * O_POSMESHPICTRESOL;     /* Rescale extents */
  picdelt.y *= picscale * O_POSMESHPICTRESOL;

  for (i = 0; i < grafptr->vertnbr; i ++) {
    pictab[i].pos.x = (pictab[i].pos.x - picmin.x) * picscale * O_POSMESHPICTRESOL; /* Rescale coordinates */
    pictab[i].pos.y = (pictab[i].pos.y - picmin.y) * picscale * O_POSMESHPICTRESOL;
  }

  if (O_outParam.PosMesh.disk == 'd') {           /* If disks wanted */
    for (i = 0, j = 0; i < grafptr->vertnbr; i ++) {
      pictab[i].rad = 1e30;                       /* Assume huge square of radius */
      for ( ; j < grafptr->vendtab[i]; j ++) {
        k = grafptr->edgetab[j];
        picsrad = (pictab[i].pos.x - pictab[k].pos.x) *
                  (pictab[i].pos.x - pictab[k].pos.x) +
                  (pictab[i].pos.y - pictab[k].pos.y) *
                  (pictab[i].pos.y - pictab[k].pos.y);
        if (picsrad < pictab[i].rad)              /* Get smallest square of radius */
          pictab[i].rad = picsrad;
      }
      pictab[i].rad = sqrt (pictab[i].rad) / 2.0; /* Keep the half-distance for radius */
      if (pictab[i].rad < 1.0L)                  /* Always get a non-zero radius       */
        pictab[i].rad = 1.0L;

      pictab[i].vis = ((pictab[i].pos.x > - pictab[i].rad)           && /* Compute vertex visibility */
                       (pictab[i].pos.x < picdelt.x + pictab[i].rad) &&
                       (pictab[i].pos.y > - pictab[i].rad)           &&
                       (pictab[i].pos.y < picdelt.y + pictab[i].rad)) ? 1 : 0;
    }
  }
  else {                                          /* If disks not wanted */
    for (i = 0; i < grafptr->vertnbr; i ++)
      pictab[i].vis = ((pictab[i].pos.x > 0.0L)      && /* Compute vertex visibility */
                       (pictab[i].pos.x < picdelt.x) &&
                       (pictab[i].pos.y > 0.0L)      &&
                       (pictab[i].pos.y < picdelt.y)) ? 1 : 0;
  }
  for (i = 0; i < grafptr->vertnbr; i ++) {
    pictab[i].pos.x += 0.5L;                      /* Prepare to switch to integer coordinates */
    pictab[i].pos.y += 0.5L;
  }
  picdelt.x += 0.5L;
  picdelt.y += 0.5L;

  if (O_outParam.PosMesh.color == 'c') {          /* If color output               */
    for (i = 0; i < grafptr->vertnbr; i ++)       /* Select color for all vertices */
      pictab[i].col = mapptr->labltab[i] % O_POSMESHCOLNBR;
  }
  else {                                          /* If gray level output                  */
    for (i = 0; i < grafptr->vertnbr; i ++) {     /* Select color for all vertices         */
      for (j = mapptr->labltab[i] & 255, k = 7, pictab[i].col = 0; /* Half-tone color      */
           j > 0;                                 /* As long as there are subdivision bits */
           j >>= 1, k --)                         /* (Same as reversing the last 8 bits )  */
        pictab[i].col |= ((j & 1) << k);
    }
  }

  for (i = 0, j = 0; i < grafptr->vertnbr; i ++) { /* For all vertices                  */
    pattab[i].nbr = 0;                            /* Compute the number of output paths */
    pattab[i].idx = grafptr->verttab[i];
    for ( ; j < grafptr->vendtab[i]; j ++) {
      if ((grafptr->edgetab[j] > i) &&            /* If it can be an output edge           */
          ((pictab[i].vis | pictab[grafptr->edgetab[j]].vis) != 0) && /* And it is visible */
          ((O_outParam.PosMesh.edge != 'r') ||    /* And it can be drawn                   */
           (mapptr->labltab[i] == mapptr->labltab[grafptr->edgetab[j]])))
        pattab[i].nbr ++;                         /* One more path to higher vertices */
    }
  }
  idxnbr = 0;                                     /* No indexes yet */
  for (i = 0; i < grafptr->vertnbr; ) {
    if (pattab[i].nbr == 0) {                     /* If no output path       */
      i ++;                                       /* Skip to the next vertex */
      continue;
    }

    j = i;                                        /* Begin with this vertex        */
    idxtab[idxnbr ++] = j;                        /* Add it to the current segment */
    do {
      for (k = pattab[j].idx; k < grafptr->vendtab[j]; k ++) { /* Search for first output    */
        if ((grafptr->edgetab[k] > j) &&          /* If it can be an output edge             */
            ((pictab[j].vis | pictab[grafptr->edgetab[k]].vis) != 0) && /* And it is visible */
            ((O_outParam.PosMesh.edge != 'r') ||  /* And it can be drawn                     */
             (mapptr->labltab[j] == mapptr->labltab[grafptr->edgetab[k]])))
          break;
      }
      pattab[j].nbr --;                           /* One less output path remaining */
      pattab[j].idx = k + 1;                      /* Search from the next position  */
      j = grafptr->edgetab[k];                    /* Get the path end vertex number */
      idxtab[idxnbr ++] = j;                      /* Add it to the current segment  */
    } while (pattab[j].nbr > 0);                  /* As long as there is a path     */
    idxtab[idxnbr ++] = ~0;                       /* Mark end of path               */
  }

  if (O_outParam.PosMesh.type == 'e') {           /* EPSF-type output */
    fprintf (stream, "%%!PS-Adobe-2.0 EPSF-2.0\n");
    fprintf (stream, "%%%%Title: %s %s %s\n",
             C_filenamesrcinp, C_filenamegeoinp, C_filenamemapinp);
    fprintf (stream, "%%%%Creator: Scotch/gout\n");
    fprintf (stream, "%%%%CreationDate: %s", ctime (&pictime));
    fprintf (stream, "%%%%BoundingBox: 0 0 %d %d\n",
             (int) ((picdelt.x * O_PSDPI) / O_POSMESHPICTRESOL),
             (int) ((picdelt.y * O_PSDPI) / O_POSMESHPICTRESOL));
    fprintf (stream, "%%%%Pages: 0\n");
    fprintf (stream, "%%%%EndComments\n");
  }
  else {                                          /* Full page output */
    fprintf (stream, "%%!PS-Adobe-2.0\n");
    fprintf (stream, "%%%%Title: %s %s %s\n",
             C_filenamesrcinp, C_filenamegeoinp, C_filenamemapinp);
    fprintf (stream, "%%%%Creator: Scotch/gout\n");
    fprintf (stream, "%%%%CreationDate: %s", ctime (&pictime));
  }

  fprintf (stream, "/A  { 0 360 arc fill } bind def\n"); /* Macro definitions */
  if (O_outParam.PosMesh.color == 'c') {          /* If color output          */
    int                 i;

    for (i = 0; i < O_POSMESHCOLNBR; i ++) {      /* Build color indices */
      outColorColor (i, color);
      fprintf (stream, "/C%c { %g %g %g setrgbcolor } bind def\n",
               ('a' + i), color[0], color[1], color[2]);
    }
  }
  fprintf (stream, "/G  { 255 div setgray } bind def\n");
  fprintf (stream, "/L  { lineto stroke } bind def\n");
  fprintf (stream, "/l  { lineto } bind def\n");
  fprintf (stream, "/m  { moveto } bind def\n");

  fprintf (stream, "gsave\n");                    /* Save the context    */
  fprintf (stream, "1 setlinecap\n");             /* Perform round caps  */
  if (O_outParam.PosMesh.type == 'f')             /* If full page output */
    fprintf (stream, "%d %d translate\n",         /* Center the picture  */
             (int) ((O_PSDPI * (O_PSPAGEWIDTH  * O_POSMESHPICTRESOL - picdelt.x)) /
                    (2 * O_POSMESHPICTRESOL)),
             (int) ((O_PSDPI * (O_PSPAGEHEIGHT * O_POSMESHPICTRESOL - picdelt.y)) /
                    (2 * O_POSMESHPICTRESOL)));
  fprintf (stream, "%f %f scale\n",               /* Print scaling factor */
           (double) O_PSDPI / O_POSMESHPICTRESOL,
           (double) O_PSDPI / O_POSMESHPICTRESOL);
  fprintf (stream, "newpath 0 0 m %d 0 l %d %d l 0 %d l closepath clip\n", /* Clip picture */
           (int) picdelt.x, (int) picdelt.x,
           (int) picdelt.y, (int) picdelt.y);

  fprintf (stream, "0 G\n");                      /* Select black color */
  for (i = 0; i < idxnbr; i ++) {
    fprintf (stream, "%d\t%d\tm\n",               /* Set initial point */
             (int) pictab[idxtab[i]].pos.x,
             (int) pictab[idxtab[i]].pos.y);
    for (i ++; idxtab[i] != ~0; i ++ ) {          /* Build path */
      fprintf (stream, "%d\t%d\t%c\n",
               (int) pictab[idxtab[i]].pos.x,
               (int) pictab[idxtab[i]].pos.y,
               (idxtab[i + 1] == ~0) ? 'L' : 'l');
    }
  }

  if (O_outParam.PosMesh.disk == 'd') {           /* If disks wanted */
    for (i = 0, j = ~0; i < grafptr->vertnbr; i ++) {
      if ((pictab[i].vis > 0) &&                  /* If disk is visible              */
          (mapptr->labltab[i] != (-1))) {         /* And is mapped                   */
        if ((j == ~0) || (pictab[i].col != pictab[j].col)) { /* Update drawing color */
          if (O_outParam.PosMesh.color == 'c')
            fprintf (stream, "C%c\n", 'a' + pictab[i].col);
          else
            fprintf (stream, "%d G\n", pictab[i].col);
          j = i;                                  /* Record the new current color */
        }

        fprintf (stream, "%d %d %d A\n",          /* Draw the disk */
                (int) pictab[i].pos.x,
                (int) pictab[i].pos.y,
                (int) pictab[i].rad);
      }
    }
  }

  fprintf (stream, "grestore\n");                 /* Restore the context */
  if (O_outParam.PosMesh.type == 'f')             /* If full page output */
    fprintf (stream, "showpage\n");               /* Display the page    */

  memFree (pattab);
  memFree (idxtab);
  memFree (pictab);

  return (0);
}

/*************************************/
/*                                   */
/* This is the Tulip output routine. */
/*                                   */
/*************************************/

int
outDrawTulMesh (
const C_Graph * const       grafptr,              /* Graph structure, sorted by vertex index */
const C_Geometry * const    geomptr,              /* Graph geometry, sorted by vertex label  */
const C_Mapping * const     mapptr,               /* Result mapping, sorted by vertex label  */
FILE * const                stream)               /* Output stream                           */
{
  time_t              pictime;                    /* Creation time */
  char *              pictimeptr;
  char                pictimestr[64];
  double              color[3];                   /* Vertex color  */
  SCOTCH_Num          vertnum;
  const SCOTCH_Num *  edgetax;
  SCOTCH_Num          edgeidx;
  char                c;

  if (geomptr->verttab == NULL) {
    errorPrint ("outDrawTulMesh: geometry not provided");
    return (1);
  }

  time (&pictime);                                /* Get current time */
  pictimeptr = ctime (&pictime);
  strncpy (pictimestr, pictimeptr, 63);
  pictimestr[63] = '\0';
  pictimestr[strlen (pictimestr) - 1] = '\0';

  fprintf (stream, "(tlp \"2.0\"\n(author \"Scotch/gout\")\n(date \"%s\")\n(comment \"%s %s %s\")\n", /* Write header */
           pictimestr,
           C_filenamesrcinp, C_filenamegeoinp, C_filenamemapinp);

  if (grafptr->vertnbr == 0) {                    /* If nothing to write */
    fprintf (stream, ")\n");
    return  (0);
  }

  fprintf (stream, "(nodes\n");                   /* Write node list */
  for (vertnum = 0; vertnum < (grafptr->vertnbr - 1); vertnum ++)
    fprintf (stream, SCOTCH_NUMSTRING "%c",
             (SCOTCH_Num) (vertnum + grafptr->baseval),
             ((vertnum & 7) == 7) ? '\n' : '\t');
  fprintf (stream, SCOTCH_NUMSTRING ")\n",
           (SCOTCH_Num) (vertnum + grafptr->baseval));

  edgetax = grafptr->edgetab - grafptr->baseval;
  for (vertnum = 0, edgeidx = grafptr->baseval; vertnum < grafptr->vertnbr; vertnum ++) {
    SCOTCH_Num          edgenum;
    SCOTCH_Num          edgennd;

    for (edgenum = grafptr->verttab[vertnum], edgennd = grafptr->vendtab[vertnum];
         edgenum < edgennd; edgenum ++) {
      SCOTCH_Num          vertend;

      vertend = edgetax[edgenum];
      if (vertend <= vertnum)                     /* True even if baseval=1 and as vertnum unbased */
        continue;

      fprintf (stream, "(edge " SCOTCH_NUMSTRING "\t" SCOTCH_NUMSTRING "\t" SCOTCH_NUMSTRING ")\n",
               (SCOTCH_Num) (edgeidx ++),
               (SCOTCH_Num) (vertnum + grafptr->baseval),
               (SCOTCH_Num) vertend);
    }
  }

  fprintf (stream, "(property 0 layout \"viewLayout\"\n"); /* Write node coordinates */
  c = '\n';
  for (vertnum = 0; vertnum < grafptr->vertnbr; vertnum ++) {
    if (vertnum == (grafptr->vertnbr - 1))
      c = ')';
    fprintf (stream, "(node " SCOTCH_NUMSTRING "\t\"(%lf,%lf,%lf)\")%c",
             (SCOTCH_Num) (vertnum + grafptr->baseval),
             (double) geomptr->verttab[vertnum].x,
             (double) geomptr->verttab[vertnum].y,
             (double) geomptr->verttab[vertnum].z,
             c);
  }
  fprintf (stream, "\n");

  if (O_outParam.TulMesh.color == 'c') {
    fprintf (stream, "(property 0 color \"viewColor\"\n(default \"(255,255,255,255)\" \"(0,0,0,0)\")\n"); /* Write node color values */
    c = '\n';
    for (vertnum = 0; vertnum < grafptr->vertnbr; vertnum ++) {
      if (vertnum == (grafptr->vertnbr - 1))
        c = ')';
      outColorColor (mapptr->labltab[vertnum], color);
      fprintf (stream, "(node " SCOTCH_NUMSTRING " \"(%d,%d,%d,255)\")%c",
               (SCOTCH_Num) (vertnum + grafptr->baseval),
               (int) (color[0] * 255.0),
               (int) (color[1] * 255.0),
               (int) (color[2] * 255.0),
               c);
    }
    fprintf (stream, "\n");
  }

  fprintf (stream, "(property 0 size \"viewSize\"\n(default \"(0,0,0)\" \"(0,0,0)\")"); /* Write default node size */
  if (O_outParam.TulMesh.disk == 'd') {           /* If disks wanted */
    const C_GeoVert *   geomtax;

    geomtax = geomptr->verttab - grafptr->baseval;
    fprintf (stream, "\n");
    c = '\n';
    for (vertnum = 0; vertnum < grafptr->vertnbr; vertnum ++) {
      SCOTCH_Num          edgenum;
      SCOTCH_Num          edgennd;
      double              distmin;
      C_GeoVert           vertpos;

      if (vertnum == (grafptr->vertnbr - 1))
        c = ')';

      distmin = 1e30;                             /* Huge distance assumed */
      vertpos.x = geomptr->verttab[vertnum].x;
      vertpos.y = geomptr->verttab[vertnum].y;
      vertpos.z = geomptr->verttab[vertnum].z;
      for (edgenum = grafptr->verttab[vertnum], edgennd = grafptr->vendtab[vertnum];
           edgenum < edgennd; edgenum ++) {
        SCOTCH_Num          vertend;
        double              distval;

        vertend = edgetax[edgenum];
        distval = (geomtax[vertend].x - vertpos.x) * (geomtax[vertend].x - vertpos.x) +
                  (geomtax[vertend].y - vertpos.y) * (geomtax[vertend].y - vertpos.y) +
                  (geomtax[vertend].z - vertpos.z) * (geomtax[vertend].z - vertpos.z);
        if (distval < distmin)
          distmin = distval;
      }
      distmin = sqrt (distmin) * (0.5 * O_TULMESHDISKRATIO);
      fprintf (stream, "(node " SCOTCH_NUMSTRING " \"(%lf,%lf,%lf)\")%c",
               (SCOTCH_Num) (vertnum + grafptr->baseval),
               distmin, distmin, distmin, c);
    }
    fprintf (stream, "\n");
  }
  else
    fprintf (stream, ")\n");

  fprintf (stream, ")\n");

  return (0);
}

/*****************************************/
/*                                       */
/* This is the VTK output routine, based */
/* on the OpenInventor routine.          */
/*                                       */
/*****************************************/

int
outDrawVtkMesh (
const C_Graph * const       grafptr,              /* Graph structure, sorted by vertex index */
const C_Geometry * const    geomptr,              /* Graph geometry, sorted by vertex label  */
const C_Mapping * const     mapptr,               /* Result mapping, sorted by vertex label  */
FILE * const                stream)               /* Output stream                           */
{
  O_VtkMeshPath *     pathtab;                    /* Array of path building data */
  SCOTCH_Num          pathnbr;                    /* Number of paths created     */
  SCOTCH_Num          pathnum;
  SCOTCH_Num *        indxtab;                    /* Array of indexes            */
  SCOTCH_Num          indxnbr;                    /* Number of indexes           */
  SCOTCH_Num          indxnum;
  SCOTCH_Num          vertnum;
  SCOTCH_Num          edgenum;
  time_t              timedat;                    /* Creation time               */

  if (geomptr->verttab == NULL) {
    errorPrint ("outDrawVtkMesh: geometry not provided");
    return (1);
  }

  time (&timedat);                                /* Get current time */

  if (memAllocGroup ((void **) (void *)
                     &indxtab, (size_t) ((grafptr->edgenbr / 2) * 3 * sizeof (SCOTCH_Num)),
                     &pathtab, (size_t) (grafptr->vertnbr           * sizeof (O_VtkMeshPath)), NULL) == NULL) {
    errorPrint ("outDrawVtkMesh: out of memory");
    return (1);
  }

  for (vertnum = edgenum = 0; vertnum < grafptr->vertnbr; vertnum ++) { /* Compute number of output paths For all vertices */
    pathtab[vertnum].nbr = 0;
    pathtab[vertnum].idx = grafptr->verttab[vertnum];

    for ( ; edgenum < grafptr->vendtab[vertnum]; edgenum ++) {
      SCOTCH_Num          vertend;

      vertend = grafptr->edgetab[edgenum];
      if ((vertend > vertnum) &&                  /* If it can be an output edge */
          ((O_outParam.VtkMesh.edge != 'r') ||    /* And this edge can be drawn  */
           (mapptr->labltab[vertnum] == mapptr->labltab[vertend])))
        pathtab[vertnum].nbr ++;                  /* One more path to higher vertices */
    }
  }

  indxnbr = 0;                                    /* No indexes yet  */
  pathnbr = 0;                                    /* No paths either */

  for (vertnum = 0; vertnum < grafptr->vertnbr; ) { /* For all vertices                    */
    SCOTCH_Num          indxtmp;                  /* Index where to place number of points */
    SCOTCH_Num          verttmp;

    if (pathtab[vertnum].nbr == 0) {              /* If no output path for this vertex */
      vertnum ++;                                 /* Skip to next vertex               */
      continue;
    }

    indxtmp = indxnbr ++;                         /* Save space for number of points */
    verttmp = vertnum;                            /* Begin with this vertex          */
    indxtab[indxnbr ++] = verttmp;                /* Add it to the current segment   */
    do {
      SCOTCH_Num          edgenum;
      SCOTCH_Num          vertend;

      edgenum = pathtab[verttmp].idx;             /* Start searching from last unsearched edge */
      do {                                        /* Search for first valid output edge        */
        vertend = grafptr->edgetab[edgenum];
        if ((vertend > verttmp) &&                /* If it can be an output edge */
            ((O_outParam.VtkMesh.edge != 'r') ||  /* And this edge can be drawn  */
             (mapptr->labltab[verttmp] == mapptr->labltab[vertend])))
          break;
      } while (++ edgenum < grafptr->vendtab[verttmp]);

      pathtab[verttmp].nbr --;                    /* One less output path remaining */
      pathtab[verttmp].idx = edgenum + 1;         /* Search from the next position  */
      verttmp = vertend;                          /* Get the path end vertex number */
      indxtab[indxnbr ++] = verttmp;              /* Add it to the current segment  */
    } while (pathtab[verttmp].nbr > 0);           /* As long as there is a path     */
    indxtab[indxtmp] = indxnbr - indxtmp - 1;     /* Set size of created path       */
    pathnbr ++;                                   /* One more path created          */
  }

  fprintf (stream, "# vtk DataFile Version 2.0\n"); /* Write header */
  fprintf (stream, "%s %s %s | Created by Scotch/gout | %sASCII\n",
           C_filenamesrcinp, C_filenamegeoinp, C_filenamemapinp,
           ctime (&timedat));

  if (indxnbr == 0)                               /* If nothing to write */
    return (0);

  fprintf (stream, "\nDATASET UNSTRUCTURED_GRID\n");

  fprintf (stream, "\nPOINTS " SCOTCH_NUMSTRING " float\n",
           grafptr->vertnbr);
  for (vertnum = 0; vertnum < grafptr->vertnbr; vertnum ++)
    fprintf (stream, "%g\t%g\t%g\n",
             geomptr->verttab[vertnum].x,
             geomptr->verttab[vertnum].y,
             geomptr->verttab[vertnum].z);

  fprintf (stream, "\nCELLS " SCOTCH_NUMSTRING " " SCOTCH_NUMSTRING "\n",
           pathnbr, indxnbr);
  for (indxnum = 0; indxnum < indxnbr; ) {
    SCOTCH_Num          pontnbr;                  /* Number of points in current segment */    
    SCOTCH_Num          indxtmp;

    pontnbr = indxtab[indxnum];
    for (indxtmp = indxnum + pontnbr; indxnum < indxtmp; )
      fprintf (stream, SCOTCH_NUMSTRING "\t", indxtab[indxnum ++]);
    fprintf (stream, SCOTCH_NUMSTRING "\n", indxtab[indxnum ++]);
  }

  fprintf (stream, "\nCELL_TYPES " SCOTCH_NUMSTRING "\n", /* All cells ate poly-line paths */
           pathnbr);
  for (pathnum = 0; pathnum < pathnbr; pathnum ++)
    fprintf (stream, "4\n");

  fprintf (stream, "\nPOINT_DATA " SCOTCH_NUMSTRING "\nSCALARS mapValues int\nLOOKUP_TABLE default\n",
           grafptr->vertnbr);
  for (vertnum = 0; vertnum < grafptr->vertnbr; vertnum ++) {
    SCOTCH_Num          mappval;

    mappval = mapptr->labltab[vertnum];
    fprintf (stream, SCOTCH_NUMSTRING "\n",
             (mappval == -1) ? 0 : (mappval + 1)); /* Unmapped vertices are of VTK color 0 (white) */
  }

  memFree (indxtab);                              /* Free group leader */

  return (0);
}
