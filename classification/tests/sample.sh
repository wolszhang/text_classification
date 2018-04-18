python ../bin/pre_process.py ../sample_corpus.txt ../sample_corpus2.txt ../test ../train
python ../bin/naive_bayes.py ../train ../test > log.txt
python ../bin/k_naive_bayes.py ../train ../test ../bin/vectors.pcl
python ../bin/token_svm.py -emb ../bin/vectors.pcl -train ../train -test ../test 
