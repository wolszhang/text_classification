all: 
	@g++ ./naive/naive.cpp -o ./naive/naive
	@./naive/naive ./data/input1_train ./data/input2_train ./data/input1_test ./data/input2_test

	@./liblinear-2.11/train -s 2 -c 1 -e 0.1 -B 1 ./data/trainw.txt model
	@./liblinear-2.11/predict ./data/testw.txt model output1
	@python vote.py ./word2vec/1 ./word2vec/-1 output1 ./word2vec/count.txt

	@./liblinear-2.11/train -s 0 -c 1 -e 0.1 -B 1 ./data/trainw.txt model
	@./liblinear-2.11/predict -b ./data/testw.txt model output2
	@python vote.py ./word2vec/1 ./word2vec/-1 output2 ./word2vec/count.txt

	@./liblinear-2.11/train -s 2 -c 1 -e 0.1 -B 1 ./data/train.txt model
	@./liblinear-2.11/predict ./data/test.txt model output3
	@python check_acc.py ./output3 333
