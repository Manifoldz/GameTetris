FROM ubuntu

RUN apt-get update && apt-get install -y \
  gcc make valgrind vim check libncurses5-dev libncursesw5-dev

COPY . /code

WORKDIR /code

CMD /bin/bash
