<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <link rel="stylesheet" href="l5-stylesheet.css">
    <title>Tax Calculator</title>
</head>
<body>
    <center>
        <h1><a href="../index.html"><b>Taylor's Website</b></a></h1> <br />
        <table style="border-spacing: 100px 0">
            <tr>
                <td><a href="../lab1/index.html">lab1</a></td>
                <td><a href="../lab2/index.html">lab2</a></td>
                <td><a href="../lab3/index.html">lab3</a></td>
                <td><a href="../lab4/index.html">lab4</a></td>
                <td><a href="../lab5/index.html">lab5</a></td>
                <td><a href="../lab6/index.html">lab6</a></td>
                <td><a href="../lab7/index.html">lab7</a></td>
                <td><a href="../lab8/index.html">lab8</a></td>
            </tr>
        </table>
    <hr />
    </center>
    <h1>Sales Tax Calculator</h1>
    <form action="<?=$_SERVER['PHP_SELF']?>" method="post">
        <?php
            if(isset($_POST["submit"])) {
                if(!is_numeric($_POST["amount"]) || !is_numeric($_POST["rate"])) {
                    echo "<div style='color: red; background-color: gray; width: 350px'>
                        Amount must be a numeric value!<br />Rate must be a numeric value!
                        <br />Cannot calculate!</div><br/>";
                    echo "<input type='submit' name='return' value='Return to Calculator'>";
                }
                else if($_POST["amount"] < 0 || $_POST["rate"] < 0) {
                    echo "<div style='color: red; background-color: gray; width:350px'>
                        Amount must be a non-negative value!<br />Rate must be a non-negative value!
                        <br />Cannot calculate!</div><br />";
                    echo "<input type='submit' name='return' value='Return to Calculator'>";
                }
                else {
                    $amount = $_POST["amount"];
                    $rate = $_POST["rate"];
                    echo "Entered Amount: $" . $amount . "<br />";
                    echo "Entered Tax Rate: " . $rate . "%<br />";
                    echo "Calculated Tax Amount: $" . number_format((($amount * ($rate/100)) + $amount), 2) . "<br />";
                    echo "<input type='submit' name='return' value='Return to Calculator'>";
                }
            }
            else {
                echo "Amount: $<input type='text' name='amount'><br />";
                echo "Tax Rate: <input type='text' name='rate'>%<br />";
                echo "<input type='submit' name='submit' value='Calculate'>";
            }
        ?>
    </form>
    <div style="padding-top: 20px;">
        <a href="index.html">Lab 6 Index</a>
    </div>
</body>
</html>