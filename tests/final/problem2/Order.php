<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <title>Document</title>
</head>
<body>
    <form action="<?=$_SERVER['PHP_SELF'] ?>" method="post">
        Amount of Child Tickets to be Purchased ($4 each): <input type="int" name="child"/><br/>
        Amount of Adult Tickets ot be Purchased ($6 each): <input type="int" name="adult"/><br/>
        <input type="submit" name="submit" value="Submit" /></br></br></br>
        <?php
            $servername = "localhost";
            $username = "root";
            $password = "Gggoooooossseee777!!!";
            $conn = new mysqli($servername, $username, $password);
    
            if(!$conn) {
                die("Connection failed:" . $conn->connect_error);
            }
    
            $sql = "create database if not exists CSCI332Final";
            $conn->query($sql);
    
            $sql = "use CSCI332Final";
            $conn->query($sql);
    
            $sql = "create table if not exists orders (
                    ID int not null auto_increment,
                    AdultAmt int,
                    ChildAmt int,
                    Total int,
                    primary key (ID)
            )";
            $conn->query($sql);

            $child = $_POST["child"];
            $adult = $_POST["adult"];
            $total = ($child * 4) + ($adult * 6);
            if(isset($_POST['submit'])) {
                echo "Total Price: $" . $total;
                
                $sql = "insert into orders (AdultAmt, ChildAmt, Total) values (
                        '" . $child . "',
                        '" . $adult . "',
                        '" . $total . "'
                );";
                $conn->query($sql);

                echo "</br</br><a href='Detail.php'>Details</a>";
            }

            $conn->close();
        ?>
    </form>
</body>
</html>