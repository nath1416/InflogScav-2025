# ===== Build stage =====
FROM debian:trixie-slim AS build

RUN apt-get update && \
    apt-get install -y \
      libglew-dev libglfw3-dev libglm-dev \
      cmake git build-essential pkg-config \
      mesa-utils libgl1-mesa-dev libegl1-mesa-dev && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . .
RUN mkdir build && cd build && cmake .. && make -j"$(nproc)"

# ===== Runtime stage =====
FROM debian:trixie-slim AS runtime

RUN apt-get update && \
    apt-get install -y \
      libglew2.2 libglfw3 libglm-dev \
      libgl1-mesa-dri libglx-mesa0 libegl1 && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app

# copy binary
COPY --from=build /app/build/cube ./cube

# copy shaders
COPY --from=build /app/shaders ./shaders

# if you have textures/models:
# COPY --from=build /app/assets ./assets

CMD ["./cube"]
