REF 
+ https://www.pwg.org/ipp/ippguide.html<br>
+ https://www.pwg.org/ipp/everywhere.html<br>

# 1. 打印JOB
## 示例1
`$ ipptool -v -t -f ~/swap/TestData/A41L.pdf ipp://xxxxxcf9d6c.local:631/ipp/print print-job.test `<br>
`"print-job.test":`<br>
    &nbsp;&nbsp;`Print-Job:`<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`attributes-charset (charset) = utf-8`<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`attributes-natural-language (naturalLanguage) = en`<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`printer-uri (uri) = ipp://xxxxxcf9d6c.local:631/ipp/print`<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`requesting-user-name (nameWithoutLanguage) = tess`<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`document-format (mimeMediaType) = application/pdf`<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`copies (integer) = 1`<br>
    `Print file using Print-Job                                           [PASS]`<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`RECEIVED: 257 bytes in response`<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`status-code = successful-ok (successful-ok)`<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`attributes-charset (charset) = utf-8`<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`attributes-natural-language (naturalLanguage) = zh-cn`<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`job-uri (uri) = ipp://xxxxxcf9d6c.local:631/ipp/print/job-10`<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`job-id (integer) = 10`<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`job-state (enum) = pending`<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`job-state-reasons (keyword) = job-incoming`<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`job-uuid (uri) = urn:uuid:1245a700-499f-11d5-8004-f4a997cf9d6c`<br>

## 示例2
`$ ipptool -v -t -f ./tess-print-job.test ipp://xxxxxcf9d6c.local:631/ipp/print print-job.test `<br>
`"print-job.test":`<br>
    `Print-Job:`<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`attributes-charset (charset) = utf-8`<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`attributes-natural-language (naturalLanguage) = en`<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`printer-uri (uri) = ipp://xxxxxcf9d6c.local:631/ipp/print`<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`requesting-user-name (nameWithoutLanguage) = tess`<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`document-format (mimeMediaType) = application/octet-stream`<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`copies (integer) = 1`<br>
    `Print file using Print-Job                                           [PASS]`<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`RECEIVED: 257 bytes in response`<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`status-code = successful-ok (successful-ok)`<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`attributes-charset (charset) = utf-8`<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`attributes-natural-language (naturalLanguage) = zh-cn`<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`job-uri (uri) = ipp://xxxxxcf9d6c.local:631/ipp/print/job-11`<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`job-id (integer) = 11`<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`job-state (enum) = pending`<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`job-state-reasons (keyword) = job-incoming`<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`job-uuid (uri) = urn:uuid:30c719c0-499f-11d5-8004-f4a997cf9d6c`<br>

## 示例3<br>
因为打印机不支持text/plain格式，所以这个一个打印失败的sample<br>
`$ ipptool -v -t -f ./tess-print-job.test -d filetype=text/plain ipp://xxxxxcf9d6c.local:631/ipp/print print-job.test `<br>
`"print-job.test":`<br>
    `Print-Job:`<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`attributes-charset (charset) = utf-8`<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`attributes-natural-language (naturalLanguage) = en`<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`printer-uri (uri) = ipp://xxxxxcf9d6c.local:631/ipp/print`<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`requesting-user-name (nameWithoutLanguage) = tess`<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`document-format (mimeMediaType) = text/plain`<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`copies (integer) = 1`<br>
    `Print file using Print-Job                                           [FAIL]`<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`RECEIVED: 75 bytes in response`<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`status-code = client-error-document-format-not-supported (client-error-document-format-not-supported)`<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`attributes-charset (charset) = utf-8`<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`attributes-natural-language (naturalLanguage) = zh-cn`<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`EXPECTED: STATUS successful-ok (got client-error-document-format-not-supported)`<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`EXPECTED: STATUS successful-ok-ignored-or-substituted-attributes (got client-error-document-format-not-supported)`<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`EXPECTED: job-id`<br>
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`EXPECTED: job-uri`<br>


# 2. 获取JOB的状态 <br>
`$ ipptool ipp://xxxxxcf9d6c.local:631/ipp/print get-completed-jobs.test` <br>
`job-id job-state job-name job-originating-user-name job-media-sheets-completed`<br>
`------ --------- -------- ------------------------- --------------------------`<br>
`11     completed          tess                      0                         `<br>
`10     completed          tess                      0                         `<br>
`9      completed          tess                      0                         `<br>
`8      aborted            tess                      0  `<br>

# 3. 获取打印机能力 <br>
`$ ipptool -tI ipp://xxxxxcf9d6c.local:631/ipp/print ~/get-printer-attributes-suite.test.txt ` <br>
`"/home/tess/get-printer-attributes-suite.test.txt":`<br>
    `Get-Printer-Attributes (no requested-attributes)                     [PASS]`<br>
    `Get-Printer-Attributes (requested-attributes='all')                  [PASS]`<br>
    `Get-Printer-Attributes (requested-attributes='all','media-col-databa [PASS]`<br>
    `Get-Printer-Attributes (requested-attributes='none')                 [FAIL]`<br>