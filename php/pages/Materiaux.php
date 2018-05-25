<p id="elementTitle">Ajouter un matériaux</p>

<p class="elementDesc">Couleur entre 0 et 255<br/>Rélféxion en pourcentage</p>

<form id="formParameters" method="POST" action="./php/controller.php">
    <p class="elementDesc">Début de l'animation</p>

    <div class="inputParameter">
        <label for="nom">Nom:</label>   
        <input type="text" id="nom" name="nom" />
    </div>
    <div class="inputParameter">
        <label for="R">Rouge:</label>   
        <input type="number" id="R" name='R' step="1"/>
    </div>
    <div class="inputParameter">
        <label for="G">Vert:</label>   
        <input type="number" id="G" name='G' step="1"/>
    </div>
    <div class="inputParameter">
        <label for="B">Bleu:</label>   
        <input type="number" id="B" name='B' step="1"/>
    </div>
    
    
    <p class="elementDesc">Fin de l'animation</p>
    <div class="inputParameter">
        <label for="Rend">Rouge:</label>   
        <input type="number" id="Rend" name='Rend' step="1"/>
    </div>
    <div class="inputParameter">
        <label for="Gend">Vert:</label>   
        <input type="number" id="Gend" name='Gend' step="1"/>
    </div>
    <div class="inputParameter">
        <label for="Bend">Bleu:</label>   
        <input type="number" id="Bend" name='Bend' step="1"/>
    </div>
    
    <div class="inputParameter">
        <input type="submit"  name="addMateriaux" value="Ajouter"/>
    </div>
</form>



