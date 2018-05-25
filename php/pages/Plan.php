<p id="elementTitle">Ajouter un Plan</p>

<p class="elementDesc">Ax+By+Cz+D=0</p>

<form id="formParameters" method="POST" action="./php/controller.php">
    <div class="inputParameter">
        <label for="A">A:</label>   
        <input type="number" id="A" name='A' step="0.1"/>
    </div>
    <div class="inputParameter">
        <label for="B">B:</label>   
        <input type="number" id="B" name='B' step="0.1"/>
    </div>
    <div class="inputParameter">
        <label for="C">C:</label>   
        <input type="number" id="C" name='C' step="0.1"/>
    </div>
    <div class="inputParameter">
        <label for="D">D:</label>   
        <input type="number" id="D" name='D' step="0.1"/>
    </div>
    <div class="inputParameter">
        <select name='materiaux'>
            <?php
               foreach($_SESSION["allMateriaux"] as $mat){
                   echo "<option>".$mat[1]."</option>";
               }
            ?>
        </select>
    </div>
    
    
    <div class="inputParameter">
        <label for="Aend">A:</label>   
        <input type="number" id="Aend" name='Aend' step="0.1"/>
    </div>
    <div class="inputParameter">
        <label for="Bend">B:</label>   
        <input type="number" id="Bend" name='Bend' step="0.1"/>
    </div>
    <div class="inputParameter">
        <label for="Cend">C:</label>   
        <input type="number" id="Cend" name='Cend' step="0.1"/>
    </div>
    <div class="inputParameter">
        <label for="Dend">D:</label>   
        <input type="number" id="Dend" name='Dend' step="0.1"/>
    </div>
    <div class="inputParameter">
        <input type="submit"  name="addPlan" value="Ajouter"/>
    </div>
</form>



