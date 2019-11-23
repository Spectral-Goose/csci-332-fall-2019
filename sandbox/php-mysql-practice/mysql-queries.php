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
        $password = "Gggoooooossseee777!!!";
        $database = "CSCI332";
        $conn = new mysqli($servername, $username, $password, $database);

        if(!$conn) {
            die("Connection failed:" . $conn->connect_error);
        }

        $sql = "insert into students (firstname, lastname, test1, test2, test3) values 
                ('" . $_POST['first'] . "',
                 '" . $_POST['last'] . "',
                 '" . $_POST['test1'] . "',
                 '" . $_POST['test2'] . "',
                 '" . $_POST['test3'] . "');";
        echo $sql . "<br/>";
        if($conn->query($sql) == true) {
            echo "inserted successfully";
        }
        else {
            echo "failed to insert: " . $conn->error;
        }

        // create a table called students
        /*$sql = "create table student (
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
        }*/

        // create a database of CSCI315 if it doesnt already exist
        /*$sql = "create database if not exists CSCI315";
        if($conn->query($sql) == true) {
            echo "database create successfully";
        }
        else {
            echo "database creation failed";
        }*/

        // create table students in database CSCI332
        /*$sql = "create table students (ID int(6) unsigned auto_increment primary key, 
                firstname varchar(30) not null, lastname varchar(30) not 
                null, test1 int, test2 int, test3 int, grade float(10.2));";

        if($conn->query($sql) == true) {
            echo "table created successfully";
        }
        else {
            echo "table creation failed";
        }*/

        // close the connection. necessary at the end of every php script using mysql
        $conn->close();
    ?>
</body>
</html>