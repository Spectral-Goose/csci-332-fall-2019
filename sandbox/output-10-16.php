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
        /*$name = $_POST['User_Name'];
        $password = $_POST['User_Password'];

        echo "Welcome " . $name . "<br />";
        echo "I have stolen your password. Your password is " . $password . "<br />";*/

        /*$apple = $_POST['Apple'];
        $price = $_POST['Price'];

        echo "The total price for " . $apple > " aplles is $" . $apple * $price . "<br />";*/

        $weight = $_POST['weight'];
        $height = $_POST['height'];
        $BMI = $weight * 703 / ($height * $height);

        echo "Your BMI is " . $BMI . "<br />";
    ?>
</body>
</html>