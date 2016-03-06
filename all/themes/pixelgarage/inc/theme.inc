<?php
/**
 * Created by PhpStorm.
 * User: ralph
 * Date: 06.02.15
 * Time: 17:22
 */
/* =============================================================================
 *      Language block theme
 * ========================================================================== */

function pixelgarage_links__locale_block(&$vars) {
  foreach($vars['links'] as $language => $langInfo) {
    $abbr = $langInfo['language']->language;
    $vars['links'][$language]['title'] = substr($abbr, 0, 1);
  }
  $content = theme_links($vars);
  return $content;
}
