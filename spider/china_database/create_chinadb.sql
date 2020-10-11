CREATE DATABASE IF NOT EXISTS chinadb;
use chinadb;

DROP TABLE IF EXISTS area;
DROP TABLE IF EXISTS city;
DROP TABLE IF EXISTS province;

CREATE TABLE province (
    `province_id` INT AUTO_INCREMENT,
    `province_name` VARCHAR(32) NOT NULL,
    PRIMARY KEY (province_id)
) DEFAULT CHARACTER SET UTF8;

CREATE TABLE city (
    `city_id` INT AUTO_INCREMENT,
    `province_id` INT NOT NULL,
    `city_name` VARCHAR(32) NOT NULL,
    PRIMARY KEY (city_id),
    FOREIGN KEY (province_id) REFERENCES province (province_id) ON DELETE CASCADE
) DEFAULT CHARACTER SET UTF8;

CREATE TABLE area (
    `area_id` INT AUTO_INCREMENT,
    `city_id` INT NOT NULL,
    `area_name` VARCHAR(32) NOT NULL,
    `zip_code` CHAR(10) NOT NULL,       -- 邮编
    `area_code` CHAR(10) NOT NULL,      -- 区号
    PRIMARY KEY (area_id),
    FOREIGN KEY (city_id) REFERENCES city (city_id) ON DELETE CASCADE
) DEFAULT CHARACTER SET UTF8;
