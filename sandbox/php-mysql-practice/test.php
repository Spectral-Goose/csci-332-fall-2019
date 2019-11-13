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
        $servername = "localhost";
        $username = "root";
        $password = "Taydyboo7567!";
        $conn = new mysqli($servername, $username, $password);

        if(!$conn) {
            die("Connection failed:" . $conn->connect_error);
        }
        $sql = "create database if not exists CSCI332";
        if($conn->query($sql) == true) {
            echo "Database created successfully!";
        }
        else {
            echo "Error creating database:" . $conn->error;
        }
        $conn->close();
    ?>
</body>
</html>