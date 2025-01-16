FROM ubuntu:latest
RUN mkdir project
COPY gRPCinstall.sh ./project
RUN ./project/gRPCinstall.sh
COPY . ./project
# This sets up basic docker container but does not compile code
# The task is to make sure compilations occurs correctly but for 
# some reason this does not take place. Please solve this
# Note : This just sets up the repo inside docker you will 
# still have to compile it. 
# Run initialize.sh using ./initialize.sh to compile the code.
