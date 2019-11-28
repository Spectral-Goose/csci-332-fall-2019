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
        $password = "Gggoooooossseee777!!!";
        $database = "CSCI332";
        $conn = new mysqli($servername, $username, $password, $database);

        if(!$conn) {
            die("Connection failed:" . $conn->connect_error);
        }

        $sql = "select * from students";

        if($conn->query($sql) == true) {
            echo "<table border='1'>";
            echo "<tr>
                <td>First Name</td>
                <td>Last Name</td>
                <td>Test1</td>
                <td>Test2</td>
                <td>Final</td>
            </tr>";

            $result = $conn->query($sql);
            if($result->num_rows > 0) {
                while($row = $result->fetch_assoc()) {
                    echo "<tr>";
                    echo "<td>" . $row['firstname'] . "</td>";
                    echo "<td>" . $row['lastname'] . "</td>";
                    echo "<td>" . $row['test1'] . "</td>";
                    echo "<td>" . $row['test2'] . "</td>";
                    echo "<td>" . $row['test3'] . "</td>";
                    echo "</tr>";
                }
            }
            echo "</table>";
            echo "Record created successfully";
        }
        else {
            echo "failed to insert";
        }

        $conn->close();
    ?>
</body>
</html>