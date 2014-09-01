<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:csv="csv:csv">
    <xsl:output method="text" encoding="utf-8" />
    <xsl:strip-space elements="*" />

    <xsl:variable name="delimiter" select="','" />

    <csv:columns>
        <column>qn</column>
        <column>idx</column>
        <column>isDel</column>
        <column>sig</column>
        <column>anspt</column>
        <column>anypt</column>

<column>ans</column>
    </csv:columns>

    <xsl:template match="/ssn/p[1]">
        <!-- Output the CSV header
        <xsl:for-each select="document('')/*/csv:columns/*">
                <xsl:value-of select="."/>
                <xsl:if test="position() != last()">
                    <xsl:value-of select="$delimiter"/>
                </xsl:if>
        </xsl:for-each>
        <xsl:text>&#xa;</xsl:text>-->

        <xsl:for-each select="./@*">
<xsl:value-of select="name(.)"/><xsl:text>,</xsl:text>
            <xsl:for-each select="./@*">
                <xsl:value-of select="name(.)"/><xsl:text>,</xsl:text>
            </xsl:for-each>

            <xsl:if test="position() = last()">
            <xsl:text>&#xa;</xsl:text>
            </xsl:if>
        </xsl:for-each>


        <xsl:for-each select="./@*">
            <xsl:text>"</xsl:text><xsl:value-of select="."/><xsl:text>",</xsl:text>
        </xsl:for-each>

        <!-- Output rows for each matched property -->
        <xsl:apply-templates select="v" />
        hhhhs
    </xsl:template>

    <xsl:template match="ssn/p/v">

    <xsl:if test="position() = 1">
        <xsl:text>&#xa;</xsl:text>
        <xsl:text>row,</xsl:text>
        <xsl:for-each select="./@*">
            <xsl:value-of select="name(.)"/><xsl:text>,</xsl:text>
        </xsl:for-each>
        <xsl:text>&#xa;</xsl:text>
    </xsl:if>

    <xsl:value-of select="position()"/> <xsl:text>,</xsl:text>
    <xsl:for-each select="./@*">
        <xsl:text>"</xsl:text><xsl:value-of select="."/><xsl:text>",</xsl:text>
    </xsl:for-each>
    <xsl:text>&#xa;</xsl:text>

        <xsl:variable name="p" select="." />

        <!-- Loop through the columns in order -->
        <xsl:for-each select="document('')/*/csv:columnsXXX/*">
            <!-- Extract the column name and value -->
            <xsl:variable name="column" select="." />
            <xsl:variable name="value" select="$p/*[name() = $column]" />

            <!-- Quote the value if required -->
            <xsl:choose>
                <xsl:when test="contains($value, '&quot;')">
                    <xsl:variable name="x" select="replace($value, '&quot;',  '&quot;&quot;')"/>
                    <xsl:value-of select="concat('&quot;', $x, '&quot;')"/>
                </xsl:when>
                <xsl:when test="contains($value, $delimiter)">
                    <xsl:value-of select="concat('&quot;', $value, '&quot;')"/>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:value-of select="$value"/>
                </xsl:otherwise>
            </xsl:choose>

            <!-- Add the delimiter unless we are the last expression -->
            <xsl:if test="position() != last()">
                <xsl:value-of select="$delimiter"/>
            </xsl:if>
        </xsl:for-each>

        <!-- Add a newline at the end of the record
        <xsl:text>&#xa;</xsl:text>
        -->
    </xsl:template>

</xsl:stylesheet>
