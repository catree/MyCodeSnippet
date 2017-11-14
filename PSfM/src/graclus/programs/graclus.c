#include <metis.h>
#include <iostream>
using namespace std;

int boundary_points = 0;
int spectral_initialization = 0;
int cutType = 0; //cut type, default is normalized cut
int memory_saving = 0; // forbid using local search or empty cluster removing

/*************************************************************************
* multi-level weighted kernel k-means main function
**************************************************************************/
void normalizedCut()
{
  int nparts = 1, options[11];
  idxtype *part;
  float rubvec[MAXNCON], lbvec[MAXNCON];
  GraphType graph;
  char filename[256];
  int numflag = 0, wgtflag = 0, edgecut, chain_length = 0;
  int no_args = 1, levels = 0;


  cout << "Please input filename and cluster number: \n";
  cin >> filename >> nparts;
  no_args = 0;
  
  if (nparts < 2) 
  {
    printf("The number of partitions should be greater than 1!\n");
    exit(0);
  }

  ReadGraph(&graph, filename, &wgtflag);
  if (graph.nvtxs <= 0) 
  {
    cout << "Empty graph. Nothing to do.\n";
    exit(0);
  }

	levels = amax((graph.nvtxs)/(40*log2_metis(nparts)), 20*(nparts));
  
  if(graph.ncon > 1)
    cout << "  Balancing Constraints: " << graph.ncon << endl;

  part = idxmalloc(graph.nvtxs, "main: part");
  options[0] = 0;

  cout << "#Clusters: " << nparts << endl;
  if (graph.ncon == 1) 
  {
    MLKKM_PartGraphKway(&graph.nvtxs, graph.xadj, graph.adjncy, graph.vwgt, graph.adjwgt, 
			  &wgtflag, &numflag, &nparts, &chain_length, options, &edgecut, part, levels);
  }
  else 
  {
    for (int i = 0; i < graph.ncon; i++)
      rubvec[i] = HORIZONTAL_IMBALANCE;
  }

  ComputePartitionBalance(&graph, nparts, part, lbvec);
  ComputeNCut(&graph, part, nparts);

  // writes out the partition vector
  WritePartition(filename, part, graph.nvtxs, nparts); 
  
  GKfree((void **) &graph.xadj, (void **) &graph.adjncy, (void **) &graph.vwgt, (void **) &graph.adjwgt, (void **) &part, LTERM);
}

int main(int argc, char *argv[])
{
  normalizedCut();
}  


