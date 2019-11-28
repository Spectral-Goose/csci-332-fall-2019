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
        // This is a comment line
        echo "Hello world!<br />";
        Echo "This is another <span style='color: red'>hello world!</span> <br />";
        $x = 5;
        $y = "String: ";
        $z = "This is another string";
        echo $y . $z;
        $a = 2;
        echo "<br />";
        echo $a * $x;
    ?>
    <!--
    <form action="output-10-16.php" method="post">
        Name: <input type="text" name="User_Name">
        Password: <input type="password" name="User_Password">
        <input type="submit" value="Submit">
    </form>
    -->

    <!--
    <form action="output-10-16.php" method="post">
        How many apples do you want? <input type="text" name="Apple"> <br />
        Pleae enter the price of an apple. <input type="text" name="Price"> <br />
        <input type="submit" value="Submit">
    </form>
    -->

    <form action="output-10-16.php" method="post">
        What is your weight? <input type="text" name="weight"> lbs <br />
        What is your height? <input type="text" name="height"> in <br />
        <input type="submit" value="Submit">
    </form>
</body>
</html>