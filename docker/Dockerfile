FROM php:7.2-cli
#RUN apt-get update
RUN apt-get install curl
RUN docker-php-ext-install sockets
RUN mkdir /usr/src/myapp
ENV HOME /usr/src/myapp
ENV PHP_EXEC_PATH /usr/local/bin/
WORKDIR $HOME
COPY /. $HOME
EXPOSE 3000

CMD ["bash"]

#nao funciona
#ENTRYPOINT "$PHP_EXEC_PATH/php" "-S localhost:3000"

#ENTRYPOINT "$PHP_EXEC_PATH/php" "startServer.php"
#ENTRYPOINT "$PHP_EXEC_PATH/php" "socketV2.php"




#CMD ["/usr/local/bin/php", "-S localhost:3000"]

#CMD ["/usr/local/bin/php", "-S localhost:3000"]
