number=1;
all:
	@while [[ $$number -le 30 ]] ; do \
		@rm ./res$$number/report.txt \
		@number=1
all:
	while [[ ${number} -le 2 ]] ; do
		mv ./data/pair/${number}/input1.txt ./data/input1.txt 
		mv ./data/pair/${number}/input2.txt ./data/input2.txt 
		python ./cut/cut.py ./data/input1.txt ./data/input1_test ./data/input1_train 
		python ./cut/cut.py ./data/input2.txt ./data/input2_test ./data/input2_train 
		./naive/naive ./data/input1_train ./data/input2_train ./data/input1_test ./data/input2_test ./naive/data.txt ./naive/count.txt 
		python vote.py ./naive/data.txt ./naive/count.txt 2 >> res${number}/report.txt 
		rm ./naive/data.txt ./naive/count.txt 
		./compute ./data/input1_train word2vec/input1a $(NUMSC) 
		./compute ./data/input2_train word2vec/input2a $(NUMSC) 
		./compute ./data/input1_test word2vec/input1b $(NUMSC) 
		./compute ./data/input2_test word2vec/input2b $(NUMSC) 
		./remove word2vec/input1a word2vec/input2a ./data/input1_train ./data/input2_train 
		./remove2 word2vec/input1b word2vec/input2b ./data/input1_test ./data/input2_test 
		rm word2vec/input1a 
		rm word2vec/input1b 
		rm word2vec/input2a 
		rm word2vec/input2b 
		./word2vec/wd ./word2vec/vectors.bin ./data/input1_train ./data/train1w.txt 1 
		./word2vec/wd ./word2vec/vectors.bin ./data/input2_train ./data/train2w.txt -1 
		./word2vec/wd ./word2vec/vectors.bin ./data/input1_test ./data/test1w.txt 1 
		./word2vec/wd ./word2vec/vectors.bin ./data/input2_test ./data/test2w.txt -1 
		
		./word2vec/sc ./word2vec/vectors.bin ./data/input1_train ./data/train1.txt 1 
		./word2vec/sc ./word2vec/vectors.bin ./data/input2_train ./data/train2.txt -1 
		./word2vec/sc ./word2vec/vectors.bin ./data/input1_test ./data/test1.txt 1
		./word2vec/sc ./word2vec/vectors.bin ./data/input2_test ./data/test2.txt -1 
		
		./cb ./data/train1.txt ./data/train2.txt ./data/train.txt ./word2vec/count.txt 
		./cb ./data/test1.txt ./data/test2.txt ./data/test.txt ./word2vec/count.txt 
		./cb ./data/train1w.txt ./data/train2w.txt ./data/trainw.txt ./word2vec/count.txt 
		./cb ./data/test1w.txt ./data/test2w.txt ./data/testw.txt ./word2vec/count.txt 
		./dist_margin/train -s 2 -c 1 -e 0.1 -B 1 ./data/trainw.txt model >/dev/null 
		./dist_margin/predict ./data/testw.txt model output1 >/dev/null 
		python vote.py output1 ./word2vec/count.txt 3 >> res$$number/report.txt 
		./dist_margin/predict ./data/trainw.txt model output2 >/dev/null 
		python generate.py output2 ./data/trainw.txt train.txt 
		python generate.py output1 ./data/testw.txt test.txt 

		./liblinear-2.11/train -s 0 -c 1 -e 0.1 -B 0.5 ./train.txt model >/dev/null 
		./liblinear-2.11/predict -b 1 test.txt model output4 >/dev/null 
		python vote.py output4 ./word2vec/count.txt 4 >> res/{$number/report.txt 
		rm test.txt train.txt 

		./liblinear-2.11/train -s 2 -c 1 -e 0.1 -B 1 ./data/trainw.txt model >/dev/null 
		./liblinear-2.11/predict ./data/testw.txt model output3 >/dev/null 
		python vote.py output3 ./word2vec/count.txt 1 >> res/${number}/report.txt 
		((number = number + 1)) ; 
	done
	
	

	
	@done
	
	

	