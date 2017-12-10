/*
 * Copyright 2005
 *
 * mlkkm.c
 *
 * This file contains the driving routine for multi-level kernel k-means
 *
 * Started 12/2004
 * Yuqiang Guan
 *
 * Modified 9/2006
 * Brian Kulis
 *
 */

#include <metis.h>
//#include <io.h>
#include <iostream>
using namespace std;
#define __DEBUG__

int boundary_points;
int spectral_initialization;
int cutType; //cut type, default is normalized cut
int memory_saving; // forbid using local search or empty cluster removing
//char mlwkkm_fname[256]; //used to store coarsest file



// void normalizedCut(string file, unsigned int clusterNum)
// {

// }

/*************************************************************************
* multi-level weighted kernel k-means main function
**************************************************************************/

int main(int argc, char *argv[])
{
  int i, nparts = 1, options[11];
  idxtype *part;
  float rubvec[MAXNCON], lbvec[MAXNCON];
  float result;
  GraphType graph;
  char filename[256], clusterIDFile[256];
  int numflag = 0, wgtflag = 0, edgecut, chain_length;
  timer TOTALTmr, METISTmr, IOTmr;
  int no_args = 1, levels = 0;
  // cutType = 0;
  memory_saving =0;
  chain_length = 0;
  boundary_points = 0;
  spectral_initialization = 0;

  // for (argv++; *argv != NULL; argv++)
  // {
  //   strcpy(filename, *argv);
	//   nparts = atoi(*(++argv));
  //   no_args = 0;
  // }

  cout << "Please input filename and cluster number: \n";
  cin >> filename >> nparts;
  no_args = 0;
  
  if (nparts < 2) 
  {
    printf("The number of partitions should be greater than 1!\n");
    exit(0);
  }

  cleartimer(TOTALTmr);
  cleartimer(METISTmr);
  cleartimer(IOTmr);

  starttimer(TOTALTmr);
  starttimer(IOTmr);
  ReadGraph(&graph, filename, &wgtflag);
  if (graph.nvtxs <= 0) 
  {
    cout << "Empty graph. Nothing to do.\n";
    exit(0);
  }
  stoptimer(IOTmr);
  if(levels == 0)
	  levels = amax((graph.nvtxs)/(40*log2_metis(nparts)), 20*(nparts));
  //levels = graph.nvtxs/128;
  #ifdef __DEBUG__
    cout << "\n----------------------------------------------------------------------\n";
    cout << MLKKMTITLE;
    cout << "Graph Information:\n";
    cout << "  Name: " << filename << ", \n  #Vertices: " << graph.nvtxs << ", #Edges: " << graph.nedges / 2 << ", ";
  #endif
  if(graph.ncon > 1)
    cout << "  Balancing Constraints: " << graph.ncon << endl;

  part = idxmalloc(graph.nvtxs, "main: part");
  options[0] = 0;

  starttimer(METISTmr);

  cout << "#Clusters: " << nparts << endl;
  if (graph.ncon == 1) 
  {
    MLKKM_PartGraphKway(&graph.nvtxs, graph.xadj, graph.adjncy, graph.vwgt, graph.adjwgt, 
			  &wgtflag, &numflag, &nparts, &chain_length, options, &edgecut, part,levels);
  }
  else 
  {
    for (i=0; i<graph.ncon; i++)
      rubvec[i] = HORIZONTAL_IMBALANCE;
  }
  stoptimer(METISTmr);

  ComputePartitionBalance(&graph, nparts, part, lbvec);
 
  result = ComputeNCut(&graph, part, nparts);

  #ifdef __DEBUG__
    printf("\nNormalized-Cut... \n   Cut value: %7f, Balance: ", result);
    for (i=0; i < graph.ncon; i++)
      printf("%5.2f ", lbvec[i]);
    printf("\n");
  #endif

  starttimer(IOTmr);
  WritePartition(filename, part, graph.nvtxs, nparts); 
  stoptimer(IOTmr);
 
  stoptimer(TOTALTmr);
  
#ifdef __DEBUG__
  printf("\nTiming Information:\n");
  printf("  I/O:          \t\t %7.3f\n", gettimer(IOTmr));
  printf("  Clustering:   \t\t %7.3f   (Graclus time)\n", gettimer(METISTmr));
  printf("  Total:        \t\t %7.3f\n", gettimer(TOTALTmr));
  printf("----------------------------------------------------------------------\n");
#endif

  GKfree((void **) &graph.xadj, (void **) &graph.adjncy, (void **) &graph.vwgt, (void **) &graph.adjwgt, (void **) &part, LTERM);
}  


