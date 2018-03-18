number=1
depth=18
dist=2

while [[ ${depth} -gt 10 ]]; do
	((dist = 2));
	while [[ ${dist} -lt 20 ]]; do
		((number = 1)) ;
		shopt -s nullglob
		if [ ! -d "./output/level${depth}dist${dist}/" ]; then
			((dist = dist +2));
			continue
		fi
		numfiles=(./output/level${depth}dist${dist}/*)
		numfiles=${#numfiles[@]}
		if [ ${numfiles} -gt 300 ]; then
			numfiles=300
		fi
		echo "${numfiles} files in ./output/level${depth}dist${dist}/"
		while [[ ${number} -le 300 ]] ; do
			if [ ! -d "./level${depth}dist${dist}/" ]; then
				mkdir "./level${depth}dist${dist}/"
			fi
			if [ ! -d "./output/res/lv${depth}dist${dist}/" ]; then
				mkdir "./output/res/lv${depth}dist${dist}/"
			fi
			echo "pair ${number}" >> ./output/res/lv${depth}dist${dist}/report.txt 
			if [ ! -f ./output/level${depth}dist${dist}/${number}/1.txt ]; then
				echo "pair ${number} not found"
				((number = number + 1)) ; 
				continue
			fi
			rm ./level${depth}dist${dist}/*

			cp ./output/level${depth}dist${dist}/${number}/1.txt ./level${depth}dist${dist}/input1
			cp ./output/level${depth}dist${dist}/${number}/2.txt ./level${depth}dist${dist}/input2 
			python cut/cut.py ./level${depth}dist${dist}/input1 ./level${depth}dist${dist}/input1_test ./level${depth}dist${dist}/input1_train
			python cut/cut.py ./level${depth}dist${dist}/input2 ./level${depth}dist${dist}/input2_test ./level${depth}dist${dist}/input2_train

			./naive/naive ./level${depth}dist${dist}/input1_train ./level${depth}dist${dist}/input2_train ./level${depth}dist${dist}/input1_test ./level${depth}dist${dist}/input2_test ./level${depth}dist${dist}/data.txt ./level${depth}dist${dist}/count.txt 
			python vote.py ./level${depth}dist${dist}/data.txt ./level${depth}dist${dist}/count.txt 2 >> ./output/res/lv${depth}dist${dist}/report.txt 
			
			rm ./level${depth}dist${dist}/data.txt ./level${depth}dist${dist}/count.txt
			./compute ./level${depth}dist${dist}/input1_train ./level${depth}dist${dist}/input1a 
			./compute ./level${depth}dist${dist}/input2_train ./level${depth}dist${dist}/input2a  
			./compute ./level${depth}dist${dist}/input1_test ./level${depth}dist${dist}/input1b  
			./compute ./level${depth}dist${dist}/input2_test ./level${depth}dist${dist}/input2b  
			./remove ./level${depth}dist${dist}/input1a ./level${depth}dist${dist}/input2a ./level${depth}dist${dist}/input1_train ./level${depth}dist${dist}/input2_train 
			./remove2 ./level${depth}dist${dist}/input1b ./level${depth}dist${dist}/input2b ./level${depth}dist${dist}/input1_test ./level${depth}dist${dist}/input2_test 
			rm ./level${depth}dist${dist}/input1a 
			rm ./level${depth}dist${dist}/input1b 
			rm ./level${depth}dist${dist}/input2a 
			rm ./level${depth}dist${dist}/input2b 
			./word2vec/wd ./word2vec/vectors.bin ./level${depth}dist${dist}/input1_train ./level${depth}dist${dist}/train1w.txt 1 
			./word2vec/wd ./word2vec/vectors.bin ./level${depth}dist${dist}/input2_train ./level${depth}dist${dist}/train2w.txt -1 
			./word2vec/wd ./word2vec/vectors.bin ./level${depth}dist${dist}/input1_test ./level${depth}dist${dist}/test1w.txt 1 
			./word2vec/wd ./word2vec/vectors.bin ./level${depth}dist${dist}/input2_test ./level${depth}dist${dist}/test2w.txt -1 
			
			./word2vec/sc ./word2vec/vectors.bin ./level${depth}dist${dist}/input1_train ./level${depth}dist${dist}/train1.txt 1 
			./word2vec/sc ./word2vec/vectors.bin ./level${depth}dist${dist}/input2_train ./level${depth}dist${dist}/train2.txt -1 
			./word2vec/sc ./word2vec/vectors.bin ./level${depth}dist${dist}/input1_test ./level${depth}dist${dist}/test1.txt 1
			./word2vec/sc ./word2vec/vectors.bin ./level${depth}dist${dist}/input2_test ./level${depth}dist${dist}/test2.txt -1 
			
			./cb ./level${depth}dist${dist}/train1.txt ./level${depth}dist${dist}/train2.txt ./level${depth}dist${dist}/train.txt ./level${depth}dist${dist}/count.txt 
			./cb ./level${depth}dist${dist}/test1.txt ./level${depth}dist${dist}/test2.txt ./level${depth}dist${dist}/test.txt ./level${depth}dist${dist}/count.txt 
			./cb ./level${depth}dist${dist}/train1w.txt ./level${depth}dist${dist}/train2w.txt ./level${depth}dist${dist}/trainw.txt ./level${depth}dist${dist}/count.txt 
			./cb ./level${depth}dist${dist}/test1w.txt ./level${depth}dist${dist}/test2w.txt ./level${depth}dist${dist}/testw.txt ./level${depth}dist${dist}/count.txt 
			./dist_margin/train -s 2 -c 1 -e 0.1 -B 1 ./level${depth}dist${dist}/trainw.txt ./level${depth}dist${dist}/model >/dev/null 
			./dist_margin/predict ./level${depth}dist${dist}/testw.txt ./level${depth}dist${dist}/model ./level${depth}dist${dist}/output1 >/dev/null 
			python vote.py ./level${depth}dist${dist}/output1 ./level${depth}dist${dist}/count.txt 3 >> ./output/res/lv${depth}dist${dist}/report.txt 
			./dist_margin/predict ./level${depth}dist${dist}/trainw.txt ./level${depth}dist${dist}/model ./level${depth}dist${dist}/output2 >/dev/null 
			python generate.py ./level${depth}dist${dist}/output2 ./level${depth}dist${dist}/trainw.txt ./level${depth}dist${dist}/train.txt 
			python generate.py ./level${depth}dist${dist}/output1 ./level${depth}dist${dist}/testw.txt ./level${depth}dist${dist}/test.txt 

			./liblinear-2.11/train -s 0 -c 1 -e 0.1 -B 0.5 ./level${depth}dist${dist}/train.txt ./level${depth}dist${dist}/lib-model >/dev/null 
			./liblinear-2.11/predict -b 1 ./level${depth}dist${dist}/test.txt ./level${depth}dist${dist}/lib-model ./level${depth}dist${dist}/output4 >/dev/null 
			python vote.py ./level${depth}dist${dist}/output4 ./level${depth}dist${dist}/count.txt 4 >> ./output/res/lv${depth}dist${dist}/report.txt 
			rm ./level${depth}dist${dist}/test.txt ./level${depth}dist${dist}/train.txt 

			./liblinear-2.11/train -s 2 -c 1 -e 0.1 -B 1 ./level${depth}dist${dist}/trainw.txt ./level${depth}dist${dist}/lib-model2 >/dev/null 
			./liblinear-2.11/predict ./level${depth}dist${dist}/testw.txt ./level${depth}dist${dist}/lib-model2 ./level${depth}dist${dist}/output3 >/dev/null 
			python vote.py ./level${depth}dist${dist}/output3 ./level${depth}dist${dist}/count.txt 1 >> ./output/res/lv${depth}dist${dist}/report.txt 
			((number = number + 1)) ; 
		done
		((dist = dist + 2));
	done
	((depth = depth - 1));
done