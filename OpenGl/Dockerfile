FROM debian:trixie-slim

RUN apt-get update && \
    apt-get install -y libglew-dev libglfw3-dev libglm-dev cmake git build-essential libwayland-dev wayland-protocols pkg-config && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . .

RUN mkdir build && cd build && cmake .. && make -j$(nproc)

CMD ["build/cube"]
