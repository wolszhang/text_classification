make
if [ ! -e text8 ]; then
  #wget http://mattmahoney.net/dc/text8.zip -O text8.gz
  #gzip -d text8.gz -f
  curl -o text8.zip http://mattmahoney.net/dc/text8.zip
  unzip text8.zip
fi
