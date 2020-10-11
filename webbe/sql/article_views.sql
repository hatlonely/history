
-- CREATE USER 'hatlonely'@'localhost' IDENTIFIED BY 'keaiduo1';
-- CREATE DATABASE IF NOT EXISTS webbe DEFAULT CHARSET utf8 COLLATE utf8_general_ci;
-- GRANT ALL PRIVILEGES ON webbe.* TO 'hatlonely'@'localhost';

USE webbe;
CREATE TABLE article (
  `id` INT(20) NOT NULL AUTO_INCREMENT,
  `title` VARCHAR(128) NOT NULL,
  `views` INT NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`),
  UNIQUE KEY `title` (`title`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
