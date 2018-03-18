TESTSIZE=3000
NUMSC = 3
DICSIZE=20
all: 
	@g++ -Wall ./compute.cpp -o compute
	@g++ -Wall ./remove.cpp -o remove
	@g++ -Wall ./remove2.cpp -o remove2
	@./compute ../data/input1_train input1a $(NUMSC)
	@./compute ../data/input2_train input2a $(NUMSC)
	@./compute ../data/input1_test input1b $(NUMSC)
	@./compute ../data/input2_test input2b $(NUMSC)
	@./remove input1a input2a ../data/input1_train ../data/input2_train
	@./remove2 input1b input2b ../data/input1_test ../data/input2_test
	@rm compute
	@rm remove
	@rm remove2
	@rm input1a
	@rm input1b
	@rm input2a
	@rm input2b 
	@gcc -Wall ./word2.c -o wd
	@./wd ./vectors.bin ../data/input1_train ../data/train1w.txt 1
	@./wd ./vectors.bin ../data/input2_train ../data/train2w.txt -1
	@./wd ./vectors.bin ../data/input1_test ../data/test1w.txt 1
	@./wd ./vectors.bin ../data/input2_test ../data/test2w.txt -1
	@rm wd
	
	@gcc -Wall ./sentence2vec.c -o sc
	@./sc ./vectors.bin ../data/input1_train ../data/train1.txt 1
	@./sc ./vectors.bin ../data/input2_train ../data/train2.txt -1
	@./sc ./vectors.bin ../data/input1_test ../data/test1.txt 1
	@./sc ./vectors.bin ../data/input2_test ../data/test2.txt -1
	@rm sc
	
	@gcc -Wall ./combine.c -o cb
	@./cb ../data/train1.txt ../data/train2.txt ../data/train.txt
	@./cb ../data/test1.txt ../data/test2.txt ../data/test.txt

	@./cb ../data/train1w.txt ../data/train2w.txt ../data/trainw.txt 1
	@./cb ../data/test1w.txt ../data/test2w.txt ../data/testw.txt
	@rm cb
	