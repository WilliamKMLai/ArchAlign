g++ -O3 -g3 -Wall -c -fmessage-length=0 -o Alignments/ProgressiveAlignments/BestPair.o Alignments/ProgressiveAlignments/BestPair.cpp
g++ -O3 -g3 -Wall -c -fmessage-length=0 -o Alignments/ProgressiveAlignments/Chosen.o Alignments/ProgressiveAlignments/Chosen.cpp
g++ -O3 -g3 -Wall -c -fmessage-length=0 -o Metrix/Pearson.o Metrix/Pearson.cpp
g++ -O3 -g3 -Wall -c -fmessage-length=0 -o Align.o Align.cpp
g++ -O3 -g3 -Wall -c -fmessage-length=0 -o Alignments/ProgressiveAlignments/Seed.o Alignments/ProgressiveAlignments/Seed.cpp
g++ -O3 -g3 -Wall -c -fmessage-length=0 -o Transform.o Transform.cpp
g++ -O3 -g3 -Wall -c -fmessage-length=0 -o Metrix/Euclidean.o Metrix/Euclidean.cpp
g++ -O3 -g3 -Wall -c -fmessage-length=0 -o ArchAlign1_5.o ArchAlign1_5.cpp
g++ -O3 -g3 -Wall -c -fmessage-length=0 -o Alignments/ProgressiveAlignments/AbstractProgressiveAligner.o Alignments/ProgressiveAlignments/AbstractProgressiveAligner.cpp
g++ -O3 -g3 -Wall -c -fmessage-length=0 -o Alignments/AlignFactory.o Alignments/AlignFactory.cpp
g++ -O3 -g3 -Wall -c -fmessage-length=0 -o Output.o Output.cpp
g++ -O3 -g3 -Wall -c -fmessage-length=0 -o Metrix/Spearman.o Metrix/Spearman.cpp
g++ -O3 -g3 -Wall -c -fmessage-length=0 -o Config.o Config.cpp
g++ -O3 -g3 -Wall -c -fmessage-length=0 -o Node.o Node.cpp
g++ -O3 -g3 -Wall -c -fmessage-length=0 -o Metrix/AbstractMetrix.o Metrix/AbstractMetrix.cpp
g++ -O3 -g3 -Wall -c -fmessage-length=0 -o Metrix/MetrixFactory.o Metrix/MetrixFactory.cpp
g++ -O3 -o ArchAlign1_5 Transform.o Output.o Node.o Metrix/Spearman.o Metrix/Pearson.o Metrix/MetrixFactory.o Metrix/Euclidean.o Metrix/AbstractMetrix.o Config.o ArchAlign1_5.o Alignments/ProgressiveAlignments/Seed.o Alignments/ProgressiveAlignments/Chosen.o Alignments/ProgressiveAlignments/BestPair.o Alignments/ProgressiveAlignments/AbstractProgressiveAligner.o Alignments/AlignFactory.o Align.o

