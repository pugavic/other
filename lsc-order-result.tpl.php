<div class="order-property-wrapper">
    <div class="first">
        <div class="title"><?php echo $ord['first']['title'] ?></div>
        <div class="title">
            <?php echo $ord['first']['image'] ?>
        </div>
        <div class="property-list">
            <?php echo $ord['first']['image'] ?>
            <?php echo $ord['first']['property1'] ?>
            <?php echo $ord['first']['property2'] ?>
            <?php echo $ord['first']['property3'] ?>
            <?php echo $ord['first']['property4'] ?>
            <?php echo $ord['first']['property5'] ?>
        </div>

    </div>
    <div class="second">
        <div class="title"><?php echo $ord['second']['title'] ?></div>
        <div class="title">
            <?php echo $ord['second']['image'] ?>
        </div>
        <div class="property-list">
            <?php echo $ord['second']['image'] ?>
            <?php echo $ord['second']['property1'] ?>
            <?php echo $ord['second']['property2'] ?>
            <?php echo $ord['second']['property3'] ?>
            <?php echo $ord['second']['property4'] ?>
        </div>

    </div>
        <div class="third">
        <div class="title"><?php echo $ord['third']['title'] ?></div>
        <div class="title">
            <?php echo $ord['third']['image'] ?>
        </div>
        <div class="image">
            <?php if(isset($ord['third']['property4']['image'])) echo $ord['third']['property4']['image']; ?>
        </div>
        <div class="property-list">
            <?php echo $ord['third']['property1'] ?>
            <?php echo $ord['third']['property2'] ?>
            <?php echo $ord['third']['property3'] ?>
            <?php if(isset($ord['third']['property4']['title'])) echo $ord['third']['property4']['title']; ?>
        </div>

    </div>


</div>
    
    

