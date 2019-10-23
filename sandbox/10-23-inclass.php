<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <title>Input Page</title>
</head>
<body>
    <form action="<?=$_SERVER['PHP_SELF'] ?>" method="post">
        <!--
            <input type="text" name="operand1" id=""> +
        <input type="text" name="operand2" id="">
        <input type="submit" name="add" value="add">

        <input type="checkbox" name="separator" id=""> Show Separator <br />
        <input type="checkbox" name="textbox" id=""> Show TextBox <br />
        <input type="submit" name="submit" value="Show Me!">
        -->
        <?php
            if(isset($_POST["submit"])) {
                $myArray = array("Apple", "Orange", "Banana", "Pineapple");
                echo "Your favorite fruit is " . $myArray[$_POST["fruit"]] . "<br />";
                
                /*DOESNT WORK
                if($_POST["separator"]) {
                    echo "<br />";
                }
                if($_POST["textbox"]) {
                    echo "<input type='text' />";
                }*/
            }
            else {
                echo "What is your favorite fruit?<br />";
                echo "<input type='radio' name='fruit' value='0' /> Apple <br />";
                echo "<input type='radio' name='fruit' value='1' /> Orange <br />";
                echo "<input type='radio' name='fruit' value='2' /> Banana <br />";
                echo "<input type='radio' name='fruit' value='3' /> Pineapple <br />";
                echo "<input type='submit' name='submit' value='Send' />";
            }
            /*if(isset($_POST['add'])) {
                if(empty($_POST["operand1"]) || empty($_POST["operand2"])) {
                    echo "There is nothing to add!<br />";
                }
                else {
                    $o1 = intval($_POST["operand1"]);
                    $o2 = intval($_POST["operand2"]);
                    echo "The sum is " . ($o1 + $o2) . ".<br />";
                }
            }*/
        ?>
    </form>
    <!--
    <form action="output-10-23.php" method="post">
        

        Please enter a sentence <input type="text" name="userInput" id=""><br />
        Enter a word to search: <input type="text" name="userInput2" id=""><br />
        Which word are you going to replace? <input type="text" name="userInput2" id=""><br />
        What will you replace? <input type="text" name="userInput3" id="">
        <input type="submit" value="submit">
    </form>
    -->
</body>
</html>