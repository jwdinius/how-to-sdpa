docker run -it --rm \
   -v $(pwd):/home/sdpa \
   --name sdpa-c \
   --net host \
   sdpa
