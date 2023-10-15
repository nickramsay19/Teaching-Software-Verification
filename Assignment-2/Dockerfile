FROM svftools/svf:latest

#RUN ls --color=auto -R -la /home/
RUN cp /home/SVF-tools/SVF/.config.in /home/SVF-tools/SVF/svf/include/Util/config.h

WORKDIR /root/Assignment-4
COPY CMakeLists.txt *.cpp *.h ./
COPY include/ ./include/
COPY testcase/ ./testcase/

RUN cmake -B build -S .
WORKDIR ./build
RUN cmake --build .

