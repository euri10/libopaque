FROM ghcr.io/astral-sh/uv:0.5.9-python3.12-bookworm-slim AS builder
ENV UV_COMPILE_BYTECODE=1 UV_LINK_MODE=copy
WORKDIR /code
COPY pyproject.toml uv.lock /code/
RUN --mount=type=cache,target=/root/.cache/uv \
    --mount=type=bind,source=uv.lock,target=uv.lock \
    --mount=type=bind,source=pyproject.toml,target=pyproject.toml \
    uv sync --frozen --no-install-project --no-dev

COPY auth-py-js /code/auth-py-js

# hadolint ignore=DL3025
RUN --mount=type=cache,target=/root/.cache/uv \
    uv sync --frozen --no-dev

# hadolint ignore=DL3008
RUN apt-get -y update && \
    apt-get -y upgrade && \
    apt-get install -y --no-install-recommends git pkg-config build-essential libsodium-dev && \
    apt-get -y clean && \
    rm -rf /var/lib/apt/lists/*

RUN git clone https://github.com/stef/liboprf.git && \
    cd liboprf/src && \
    make && \
    make install

RUN git clone https://github.com/stef/libopaque.git && \
    cd libopaque/src && \
    make && \
    make install

RUN ldconfig

ENV PATH="/code/.venv/bin:$PATH"
EXPOSE 5000
