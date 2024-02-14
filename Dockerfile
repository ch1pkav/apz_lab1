FROM archlinux:base-devel AS base
RUN pacman -Syu --noconfirm
RUN pacman -S --noconfirm git
RUN pacman -S --noconfirm base-devel
RUN pacman -S --noconfirm cmake gcc clang
RUN pacman -S --noconfirm boost zlib
COPY . .
RUN git clone https://aur.archlinux.org/crow.git
RUN useradd --no-create-home --shell=/bin/false build && usermod -L build
RUN echo "build ALL=(ALL) NOPASSWD: ALL" >> /etc/sudoers
RUN echo "root ALL=(ALL) NOPASSWD: ALL" >> /etc/sudoers
RUN chown -R build:build /crow
USER build
WORKDIR /crow
RUN makepkg -si --noconfirm
WORKDIR /
user root
RUN rm -rf crow
ENV DOCKERIZED=1
RUN ./compile.sh -O -d -R

FROM base AS facade
COPY --from=base bin/apz_facade /usr/bin/apz_facade
CMD ["/usr/bin/apz_facade"]
EXPOSE 18080

FROM base AS logging
COPY --from=base bin/apz_logging /usr/bin/apz_logging
CMD ["/usr/bin/apz_logging"]
EXPOSE 18081

FROM base AS message
COPY --from=base bin/apz_message /usr/bin/apz_message
CMD ["/usr/bin/apz_message"]
EXPOSE 18082
