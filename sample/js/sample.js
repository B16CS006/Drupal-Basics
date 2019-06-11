jQuery(document).ready(function(){
    // jQuery('#prefix-preview').text(jQuery('#edit-title').val());
    jQuery("#submitAJAX").click(function(){
        jQuery.ajax({
            url: Drupal.settings.basePath + 'samples/article/getSample',
            data:{
                title: jQuery('#edit-title').val(),
                token: myToken,
            },
            success: function(data1){
                // console.log(data1);
                jQuery('#message-display-area').text(data1);
            }
        });
    });
    jQuery("#edit-reset").click(function(){
        // alert('asdf');
        // console.log('asdf');
        jQuery('#edit-title').val("");
        jQuery('#edit-body').val("");
    });

    // jQuery('#addNewState').click(function(){
    //     jQuery.ajax({
    //         url: Drupal.settings.basePath + 'samples/add-remove-item/add-new-state-click',
    //         success: function(data){
    //             console.log(data);
    //         }
    //     })
    // });
});