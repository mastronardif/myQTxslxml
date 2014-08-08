<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="xml" indent="yes"/>
<xsl:strip-space elements="*" />

<xsl:template match="@*|node()">
 <xsl:copy>
  <xsl:apply-templates select="@*|node()"/>
 </xsl:copy>
</xsl:template>



<xsl:template match="ssn/p/v[@id='#0C0F181B']|ssn/p/v[@id='#276D6923']"/>

</xsl:stylesheet>

<!--
<xsl:template match="ssn/p/v[@id='#276D672D']|ssn/p/v[@id='#276D6923']" />
-->
