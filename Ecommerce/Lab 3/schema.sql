CREATE DATABASE IF NOT EXISTS ecommerce;
USE ecommerce;

CREATE TABLE IF NOT EXISTS checkouts (
    id INT AUTO_INCREMENT PRIMARY KEY,
    address VARCHAR(255),
    esewa_id VARCHAR(20),
    email VARCHAR(100),
    signature VARCHAR(100)
);
