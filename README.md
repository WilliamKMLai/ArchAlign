# ArchAlign
## ArchAlign: coordinate-free chromatin alignment reveals novel architectures

https://www.ncbi.nlm.nih.gov/pubmed/21182771

### To facilitate identification and characterization of genomic functional elements, we have developed a chromatin architecture alignment algorithm (ArchAlign). ArchAlign identifies shared chromatin structural patterns from high-resolution chromatin structural datasets derived from next-generation sequencing or tiled microarray approaches for user defined regions of interest. We validated ArchAlign using well characterized functional elements, and used it to explore the chromatin structural architecture at CTCF binding sites in the human genome. 

Compile by command line:
sh compile.sh

Output File: ArchAlign1_5
Self-contained executable to be used with configuration file.

ArchAlign v.1.5 currently accepts input files in the following format:
REGION_NAME1	data	data	data	...
REGION_NAME2	data	data	data	...
...

An example of a input sample file is included. The first column must always be
the unique ID for the genomic region of interest followed by tab-delimited data.
All rows of data must contain an equal number of columns or alignment will fail.



ArchAlign v.1 uses the Configuration file to select the parameters for alignment.
The possible parameters are listed as follows:

"Alignment:"
Possible selections are "bestpair", "seed", or "chosen" which stand for a Single
Best-Pair Alignment, Seed Selection Alignment, and a Chosen Seed Alignment respectively.
Note: selection of "chosen" requires the selection of seeds

"Input File:"
Name of the input file to be aligned.

"Sliding Window:"
This is an integer representing the window to be used in alignment. For example,
an input file with 150 columns using a Sliding Window of 100 would create a window
of size 100 which slides across all 150 columns considering 50 different possible
windows.

"Reversal Status:"
"true" or "false" This command determines whether the algorithm will reverse the
sliding window. This would be used in a case where the orientation of the genomic
feature is unknown.

"Alignment Metric:"
"pearson", "spearman", or "euclidean" These are the 3 possible metrics of measurement
available for use in alignment.

"Transformation"
"none", "poisson","log","squareroot" These are the 4 possible transformation data transformations
which convert the input data files into a more compatible space for metric comparison. Log transformation
will input the lowest theoretical log value given a normal distribution in the case of a 0.

"Alignment File Output:"
This is the name of the output file containing the aligned data.

"Alignment Coordinates File Output:"
This is the name of the output file that contains the coordinates of the shifted data
in relation to the original data. The first column contains the unique ID followed by
an integer related to the shift from the left relative to the original data. The final
column contains either "Rev" or "NA" related to to whether the final window was reversed
or not respectively.

"Output Type:"
"standard" or "treeview" Outputs the aligned data in either a format identical to the input format or
in a format recognized by the program JavaTreeview

Required for Poisson and Log Transformation:
"Genome Size:"
Total size of genome in basepairs. Needed to calculate the avg tag/bp ratio

"Total Tag Count:"
Total number of extended tags in the sequencing experiment. Needed to calculate the avg tag/bp ratio

Required for Chosen Seed Alignment:
"Seed One:"
This input parameter is the name of one of the uniqID's in the input file. This parameter
is used in conjunction with a "chosen" alignment where you wish to force an alignment
with the specific genomic regions of your choice.

"Seed Two:"
This input paramter is the name of one of the uniqID's in the input file and serves as the
second seed required for a "chosen" seed alignment. Failure to input one or both of the seeds
when a chosen seed alignment is selected will abort the alignment.



Example of Command Line for ArchAlign version 1.0:
./ArchAlign Sample_Config.file
