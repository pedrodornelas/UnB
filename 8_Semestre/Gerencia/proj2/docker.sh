sudo docker pull mysql
sudo docker pull zabbix/zabbix-server-mysql
sudo docker pull zabbix/zabbix-web-nginx-mysql
sudo docker pull zabbix/zabbix-java-gateway
sudo docker pull zabbix/zabbix-agent
sudo docker images
sudo docker run --name mysql-server -t -e MYSQL_DATABASE="zabbix" -e MYSQL_USER="dornelas" -e MYSQL_PASSWORD="dornelas" -e MYSQL_ROOT_PASSWORD="dornelas" -d mysql --character-set-server=utf8 --collation-server=utf8_bin --default-authentication-plugin=mysql_native_password
sudo docker run --name zabbix-java-gateway -t --restart unless-stopped -d zabbix/zabbix-java-gateway
sudo docker run --name zabbix-server-mysql -t -e DB_SERVER_HOST="mysql-server" -e MYSQL_DATABASE="zabbix" -e MYSQL_USER="dornelas" -e MYSQL_PASSWORD="dornelas" -e MYSQL_ROOT_PASSWORD="dornelas" -e ZBX_JAVAGATEWAY="zabbix-java-gateway" --link mysql-server:mysql --link zabbix-java-gateway:zabbix-java-gateway -p 10051:10051 --restart unless-stopped -d zabbix/zabbix-server-mysql
sudo docker run --name zabbix-web-nginx-mysql -t -e DB_SERVER_HOST="mysql-server" -e MYSQL_DATABASE="zabbix" -e MYSQL_USER="dornelas" -e MYSQL_PASSWORD="dornelas" -e MYSQL_ROOT_PASSWORD="dornelas" --link mysql-server:mysql --link zabbix-server-mysql:zabbix-server -p 80:8080 --restart unless-stopped -d zabbix/zabbix-web-nginx-mysql
sudo docker run --name zabbix-agent --link mysql-server:mysql --link zabbix-server-mysql:zabbix-server -e ZBX_HOSTNAME="Zabbix server" -e ZBX_SERVER_HOST="zabbix-server" -d zabbix/zabbix-agent
sudo docker ps -a