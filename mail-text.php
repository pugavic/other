<?php

class CustomMailSystem implements MailSystemInterface {
    /**
     * Concatenate and wrap the e-mail body for plain-text mails.
     * @param $message - A message array, as described in hook_mail_alter().
     * @return -  The formatted $message.
     */
    public function format(array $message) {
        $message['body'] = implode("\n\n", $message['body']);
        return $message;
    }

    /**
     * Send an e-mail message, using Drupal variables and default settings.
     *
     * @param $message
     *   A message array, as described in hook_mail_alter().
     * @return
     *   TRUE if the mail was successfully accepted, otherwise FALSE.
     */
    public function mail(array $message) {

        $mimeheaders = array();
        foreach ($message['headers'] as $name => $value) {
            $mimeheaders[] = $name . ': ' . mime_header_encode($value);
        }
        $line_endings = variable_get('mail_line_endings', MAIL_LINE_ENDINGS);

        return fake_mail(
            $message['to'],
            mime_header_encode($message['subject']),
            preg_replace('@\r?\n@', $line_endings, $message['body']),
            join("\n", $mimeheaders)
        );
    }
}

function fake_mail($message_to = null, $subject = null, $body = null, $header = null) {
    drupal_set_message('$message_to<br/>'.$message_to.'<br/>');
    drupal_set_message('$subject<br/>'.iconv_mime_decode($subject,0, "UTF-8").'<br/>');
    drupal_set_message('$body<br/>'.$body.'<br/>');
    drupal_set_message('$header<br/>'.$header.'<br/>');
    return(TRUE);
}
   variable_set('mail_system',array('default-system' => 'CustomMailSystem'));
