rm data.txt 
rm count.txt
python sci.py input1_train input2_train input1_test input2_train
./naive input1_train input2_train input1_test input2_train data.txt count.txt
python vote.py data.txt count.txt 2