FROM ubuntu:22.04

WORKDIR /usr/src/game

RUN apt update && \
    apt install -y \
        build-essential \
        gcc \
        g++ \
        make \
        libx11-dev \
        libxcursor-dev \
        libxrandr-dev \
        libxi-dev \
        libgl1-mesa-dev \
        libglu1-mesa-dev \
        git \
        libxinerama-dev \
        libxxf86vm-dev \
        pulseaudio \
        libasound2-plugins \
        libpulse-dev

RUN git clone https://github.com/raysan5/raylib.git /usr/local/raylib
WORKDIR /usr/local/raylib/src
RUN make PLATFORM=PLATFORM_DESKTOP
RUN make install

WORKDIR /usr/src/game

COPY . .

RUN make

CMD ["./game"]