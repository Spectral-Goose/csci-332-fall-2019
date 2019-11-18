<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <title>Document</title>
</head>
<body>
    <?php
        /*
        $servername = "localhost";
        $username = "root";
        $password = "Taydyboo7567!";
        $conn = new mysqli($servername, $username, $password);

        if(!$conn) {
            die("Connection failed:" . $conn->connect_error);
        }
        $sql = "create database if not exists CSCI332";
        if($conn->query($sql) == true) {
            echo "Database created successfully!\n";
        }
        else {
            echo "Error creating database:" . $conn->error . "\n";
        }
        */

        $servername = "localhost";
        $username = "root";
        $password = "Taydyboo7567!";
        $database = "CSCI332";
        $conn = new mysqli($servername, $username, $password, $database);

        if(!$conn) {
            die("Connection failed:" . $conn->connect_error);
        }
        $sql = "create table student (
            id int(6) unsigned auto_increment primary key,
            firstname varchar(30) not null,
            lastname varchar(30) not null,
            test1 int,
            test2 int,
            final int,
            grate float(10,2)
            )";
        if($conn->query($sql) == true) {
            echo "Table created successfully!\n";
        }
        else {
            echo "Error creating table:" . $conn->error . "\n";
        }
        $conn->close();
    ?>
</body>
</html>