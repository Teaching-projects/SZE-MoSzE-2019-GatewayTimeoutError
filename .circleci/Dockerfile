FROM debian AS doxygen
RUN apt-get update && apt-get install -y\
    git\
    doxygen\
    texlive\
    texlive-latex-extra\
    texlive-lang-european\
    texlive-lang-cyrillic\
    make\
    && apt-get autoclean

FROM debian AS cppcheck
RUN apt-get update && apt-get install -y\
	  gcc\
	  g++\
      git\
	  make\
      cppcheck\
      valgrind\
	  && apt-get autoclean