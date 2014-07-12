<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <!-- Import the identity transformation. -->
  <xsl:import href="Identity.xsl"/>
  <!--
   | This will match any element's "date" attribute
   | Make the pattern more specific if this is not appropriate
   +-->



  <xsl:template match="C/SN/QUESTIONS/q/@n">
     <!-- This will construct a "date" attribute having value of its content -->
     <xsl:attribute name="n">
       <!-- Change what's in here to construct the "new" date format -->
       <xsl:value-of select="concat('newcsnQqn-',.)"/>
     </xsl:attribute>
  </xsl:template>

<!-- -->
  <xsl:template match="C/SN/@n">
     <!-- This will construct a "date" attribute having value of its content -->
     <xsl:attribute name="n">
       <!-- Change what's in here to construct the "new" date format -->
       <xsl:value-of select="concat('newcsnn-',.)"/>
     </xsl:attribute>
  </xsl:template>

  <xsl:template match="@nm">
     <!-- This will construct a "date" attribute having value of its content -->
     <xsl:attribute name="n">
       <!-- Change what's in here to construct the "new" date format -->
       <xsl:value-of select="concat('new',.)"/>
     </xsl:attribute>
  </xsl:template>

</xsl:stylesheet>


<!--




<xsl:stylesheet version="1.0"
 xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
 xmlns:ms="http://schemas.microsoft.com/developer/msbuild/2003">
 <xsl:output omit-xml-declaration="yes" indent="yes"/>
 <xsl:strip-space elements="*"/>

 <xsl:template match="node()|@*">
  <xsl:copy>
  <xsl:apply-templates select="node()|@*"/>
  </xsl:copy>
 </xsl:template>

 <xsl:template match="ROOT/C/QUESTIONS/q/@id">
  <xsl:text>Different text</xsl:text>
 </xsl:template>
</xsl:stylesheet>

-->
