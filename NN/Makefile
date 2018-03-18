all: 
	@number=1 ; while [[ $$number -le 10 ]] ; do \
	@g++ ./naive/naive.cpp -o ./naive/naive \
	@./naive/naive ./data/input1_train ./data/input2_train ./data/input1_test ./ data/input2_test ./naive/data ./naive/count.txt \
	@python vote.py ./naive/data ./naive/count.txt 2 \
	@rm ./naive/data ./naive/count.txt \

	@./dist_margin/train -s 2 -c 1 -e 0.1 -B 1 ./data/trainw.txt model >/dev/null 
	@./dist_margin/predict ./data/testw.txt model output1 >/dev/null
	@python vote.py output1 ./word2vec/count.txt 3 \

	@./dist_margin/predict ./data/trainw.txt model output2 >/dev/null
	@python generate.py output2 ./data/trainw.txt train.txt \
	@python generate.py output1 ./data/testw.txt test.txt \

	@./liblinear-2.11/train -s 0 -c 1 -e 0.1 -B 0.5 ./train.txt model >/dev/null
	@./liblinear-2.11/predict -b 1 test.txt model output4 >/dev/null
	@python vote.py output4 ./word2vec/count.txt 4 \
	@rm test.txt train.txt \

	@./liblinear-2.11/train -s 2 -c 1 -e 0.1 -B 1 ./data/trainw.txt model >/dev/null
	@./liblinear-2.11/predict ./data/testw.txt model output3 >/dev/null
	@python vote.py output3 ./word2vec/count.txt 1 \
	@((number = number + 1)) ; \
	@done
	

	