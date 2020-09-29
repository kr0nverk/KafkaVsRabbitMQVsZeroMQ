____Apache Kafka + Zookeeper на виртуальной машине

Устанавливаем JRE
sudo apt-get update
sudo apt-get install default-jre

Если всё прошло ок, то Вы можете ввести команду
java -version

Качаем Zookeeper
wget -P /home/xpendence/downloads/ "http://apache-mirror.rbc.ru/pub/apache/zookeeper/zookeeper-3.4.12/zookeeper-3.4.12.tar.gz"
tar -xvzf /home/xpendence/downloads/zookeeper-3.4.12.tar.gz

В папке /zookeeper/conf/ есть файл zoo-sample.cfg, предлагаю переименовать его в zoo.conf, именно этот файл будет искать JVM при запуске. В этот файл нужно в конце дописать следующее:
tickTime=2000
dataDir=/var/zookeeper
clientPort=2181

Запускаем Zookeeper
bin/zkServer.sh start

После чего, предлагаю проверить, что сервер заработал. Пишем:
telnet localhost 2181
Должно появиться сообщение, что коннект удался. 

Если всё подключилось, вводим команду
ruok
Что означает: «Ты ок?» Сервер должен ответить:
imok (Я ок!)

Создаём юзера под Kafka
sudo adduser --system --no-create-home --disabled-password --disabled-login kafka

Загружаем Apache Kafka
wget -P /home/xpendence/downloads/ "http://mirror.linux-ia64.org/apache/kafka/2.1.0/kafka_2.11-2.1.0.tgz"
tar -xvzf /home/xpendence/downloads/kafka_2.11-2.1.0.tgz

Настройки находятся в /opt/kafka/config/server.properties. Добавляем одну строчку:
delete.topic.enable = true

Даём доступ юзеру kafka к директориям Kafka
chown -R kafka:nogroup /opt/kafka
chown -R kafka:nogroup /var/lib/kafka

запуск Apache Kafka
/opt/kafka/bin/kafka-server-start.sh /opt/kafka/config/server.properties

Тест работы Kafka-сервера

Для этого мы откроем два терминала, на одном запустим продюсер, на другом — консьюмер.
В первой консоли вводим по одной строчке:
/opt/kafka/bin/kafka-topics.sh --create --zookeeper localhost:2181 --replication-factor 1 --partitions 1 --topic test
/opt/kafka/bin/kafka-console-producer.sh --broker-list localhost:9092 --topic test

Должен появиться вот такой значок, означающий, что продюсер готов спамить сообщения

Во второй консоли вводим команду:
/opt/kafka/bin/kafka-console-consumer.sh --bootstrap-server localhost:9092 --topic test --from-beginning

Теперь, набирая текст в консоли-продюсере, при нажатии на Enter, он будет появляться в консоли-консьюмере.
