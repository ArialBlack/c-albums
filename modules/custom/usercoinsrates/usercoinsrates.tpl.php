<?php
  print render($form['text']);

  if (user_is_logged_in()) {
    print render($form['estimation']);
    print render($form['submit_button_1']);
    print render($form['submit_button_2']);
  }
?>
  <p class="mediana"><?php print t('Medium estimation value is: ') . '<b>' . render($form['mediana'])?></b> <a href="https://en.wikipedia.org/wiki/Median" target="_blank"><sup>?</sup></a></p>

<?php
  print render($form['table']);

  if (user_is_logged_in()) {
    print drupal_render_children($form);
  }
?>
